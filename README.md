 # boost.tmp (Tacit Meta Programming) 
 ## Warning! still work in progress
I decided to rewrite all of kvasir::mpl on a slightly different paradigm to extend compiler support further back and get some more speed out of low arity calls. Therefore most of this code has seen little or no testing beyond the skimpy unit test coverage so far. Bug reports welcome, do not use this in anything you don't want to see blow up spectacularly... yet. 
 ### What is boost.tmp?
It is my (not yet submitted to) boost general purpose metaprogramming library which covers the domains of boost.MPL, boost.Fusion, boost.mp11 and boost.hana. 
 ### Why do we need another metaprogramming library in boost?
There are a few reasons:
 - the public interface is a tacit DSL which allows for arbitrarily complex compositions of higher-order functions unlike hana and mp11
 - (often) faster compile times than code handwritten by experts due to encapsulation/leverage of intrinsics and knowledge of the users composition
 - the interface is lazy/short-circuiting by default which removes the need for things like std::conjunction, std::disjunction etc. and makes dealing with SFINAE much easier
 - (still experimental) capture and monadic propagation of SFINAE failure allows for potentially more expressive, more intuitive and sometimes faster code in SFINAE contexts
 - (still experimental) heterogeneous l-, r-value reference support (as opposed to just values in hana)
 - (still experimental) heterogeneous (fusion) support in c++11
 - The tacit DSL nature of the interface enables much of the inner workings to be left undefined allowing us to swap out the back end for either legacy or future support. This should (grain of salt here) allow code written for a c++11 compiler to benefit from c++23 (I hope) work of SG7 (just implement the call_ alias such that it passes everything on to the newfangled constexpr monster) without the need to change user code.

 ## core concepts
 ### existing concepts
Allow me to do a short review of existing metaprogramming concepts. If you are familiar with these feel free to skip ahead to new concepts.
 #### lazy metafunctions
Lazy metafunctions are implemented using class templates. 
```C++
template<typename T>
struct remove_const{  			//generic template
    using type = T;
};
template<typename T>
struct remove_const<const T>{ 	//specialization
    using type = T;
};
```
Above we are using class template specialization in order to implement a metafunction which removes const from its input parameter type. Because the pattern const T matches a smaller category of input types than the generic case it is considered more specialized and is instantiated whenever the input matches that pattern. 
This metafunction is 'lazy' in that the 'instantiation' (think 'evaluation' or 'making the damn thing') only happens when we actually 'call' the metafunction. We can 'call' this metafunction by referring to its nested type alias called type. 
```C++
template<typename T>
typename remove_const<T>::type foo(T& a);  
```
or more to the point
```C++
typedef remove_const<T> thing;    //not instantiated yet
typename thing::type i;                      //instantiated here
```
Sadly above we must use the typename disambiguator in order to tell the compiler that the name 'type' on the right-hand side of the :: is, in fact, a type and not a value, member function, template etc. This is one of the drawbacks of lazy metafunctions.

 #### eager metafunctions
C++11 gave us a few new tools, not only variadic templates but also alias templates. 
```C++
template<typename T>
using add_const = const T;
```
or 
```C++
template<typename T>
using remove_const_t = typename remove_const<T>::type;
```
One advantage to alias templates is that the compiler knows the result of an alias call is a type so we no longer need to use the typename disambiguator. It also saves us typing out ::type all over the place. One major drawback, however, is that it does not allow us to be lazy, this is actually quite subtle at first, in the SFINAE section we will dive deeper into why we cannot deprecate lazy metafunctions from our public interface.  

 #### Substitution Failure Is Not An Error (SFINAE)
SFINAE is a rule in C++ which applies to so-called **SFINAE contexts**, certain errors ([see list here](https://en.cppreference.com/w/cpp/language/sfinae)) in such contexts do not result in a compilation error (referred to as a **hard error**), rather, they result in the template specialization or function template in which the **SFINAE invocation** occurs to be removed from the set of specializations/overloads. 
```C++
void f(...) {}   //bad match but will match anything
template<typename T>
typename T::type f(T){ return {}; } //better match but will be removed by SFINAE if T does not have a ::type
```
This relates to eager vs. lazy metafunctions in a subtle way. Template instantiations do not short-circuit in the same way normal C++ expressions do. For example (thing1<T>::value || thing2<T>::value) will instantiate thing2<T> regardless of whether thing1<T>::value returned true. Metaprograms which actually short circuit in cases where our programming logic allows short-circuiting, not only have a potential efficiency gain they also save us from triggering SFINAE in an evaluation whos result is not needed because the logic should have short-circuited. 

Looking at an admittedly somewhat exotic example, let's say we want to to make sure that either our second parameter is an allocator or that both parameters have a common type (think `if(is_allocator(b) || has_common_type(a,b))`).
```C++ 
template<typename T, typename U>
std::enable_if<(is_allocator<U>::value || std::common_type_t<T,U>::value)> f(T,U);   //failed attempt, 
					//both sides are evaluated so common_type_t will 
					//SFINAE even if std::is_allocator<U>::value == true
					//also common_type_t yields a type and not a ::value

template<typename T, typename U>
std::enable_if<
    std::conditional<
        is_allocator<U>::value, 
        std::true_type, 
        std::is_convertible< std::common_type<T,U> 
    >::type::type::type::value> f(T,U);  //common pattern but its infinitely ugly
					//there are surely other 'hacks' but nothing 
					//that's not ugly and confusing
```
As we can see writing short-circuiting capable metaprogramming logic is complex, confusing and more subtly relies entirely on lazy metafunctions. On a side note the above code snippet assumes that `is_allocator` exists, it is not part of the standard library. I will present a method of implementation for `is_allocator` as well as a new way to be short-circuiting later in new concepts.

#### higher order metafunctions
Attempts at arbitrarily composable higher order metafunction are as old as metaprogramming itself, boost.MPL is the oldest popular metaprogramming library to support the concept but it seems that every template metaprogramming library since has come with its own flavor.
The basic concept introduced in boost.MPL is based entirely on lazy matafunctions
```C++
using result = transform<input_list,std::add_pointer<_1>>;
```
in the above example, the algorithm transform is passed an input sequence of types as its first parameter and a higher order metafunction as its second parameter. But wait you say, `std::add_pointer<>` is just a lazy metafunction, that's entirely correct, however, we are exploiting the fact that it is not immediately evaluated and a placeholder in order to create a kind of DSL. The fact is that this `std::add_pointer<_1>` is never instantiated as such but is 'transpiled' into the boost.MPL flavor of composed higher-order metafunctions which replaces the placeholder with the respective input type from the input list and instantiates that. 
Interestingly we can, almost, achieve arbitrarily complex compositions in this paradigm 
```C++
using input_list = mpl::vector<int,bool,char>;
using result = transform<input_list,
    std::is_same<
        std::remove_const<std::remove_reference<_1>>,
        std::add_pointer<_1>>>;
```
is roughly equivalent to
```C++
using result = mpl::vector<
    typename std::is_same<
        typename std::remove_const<typename std::remove_reference<int>::type>::type,
        typename std::add_pointer<int>::type>::type,
    typename std::is_same<
        typename std::remove_const<typename std::remove_reference<bool>::type>::type,
        typename std::add_pointer<bool>::type>::type,
    typename std::is_same<
        typename std::remove_const<typename std::remove_reference<char>::type>::type,
        typename std::add_pointer<char>::type>::type>;
```
the 'transpiler' behind the scenes is actually quite powerfull and capable of flowing the branches of a tree-like composition. There are however some caveats: only lazy metafunctions are supported, 'wrappers' (thik putting things in a list) are supported through a SFINAE test which can cause subtle surprising behavior and things get really complicated as soon as one tries to use a higher order function in another higher order function. 

Many other libraries have emerged since boost.MPL which have experimented with different kinds of higher metafunctions and composition, including my (in my opinion) failed attempt in the brigand library. Before kvasir none of them could support arbitrary complexity without a considerable performance penalty and many of them require duplication of the public interface in one form or another (like the lazy namespace in brigand or quoted and non-quoted interface in boost.mp11). 

 ### new concepts
#### metaclosures
Above I have argued that lazy metafunctions are often clunky, require disambiguators, can be a performance hit and are hard to use in short-circuiting contexts. At the same time, eager metafunctions do not compose as ergonomically as higher-order metafunctions and cannot be lazy or short-circuiting. For these reasons I came up with a new metaprogramming concept: the **metaclosure**. 
Metaclosures can be thought of as a function object with a set of 'fixed' or 'bound' arguments (think lambda capture) as well as a 'metafunction call interface' (think lambda function call operator). So far I have just been throwing made up words around so let's look at a concrete example:
```C++
using result = call_<    //we use the call_ alias to call a metaclosure
    is_<int>,        //is_ is a metaclosure which takes one fixed arguement
                     //(int in this case)
                     //and compares its to any arguement passed to it returning 
                     //true_ if the types are the same and false_ otherwise.
    int>;            //here we are passing an int to the metafunction call interface of 
                     //is_<int> resulting in (in other words call_ resolves to an alias to) true_.

using result2 = call_<is_<int>, bool>; //result2 is an alias to false_
```


                            
    

 
 ### Collaboration
I have heard from many developers who must roll their own metaprogramming library at work because their lawyers are afraid to use something open source because the ownership structure is unclear (push to a repository with a certain license does not automatically mean that you are agreeing that your contribution can be used under that license, there is also the question of whether it was, in fact, the original author who pushed the code etc. etc.). Whether or not this concern is merited is another question (and one I cannot answer as I am not a lawyer), but I have decided to retain sole authorship of this library until I can get a Contributor License Agreement (CLA) worked out which is up to snuff. If you have knowledge in this field help would be much appreciated.
I would be very happy for bug reports. I will offer this library under the boost license indefinitely (and may offer it under other licenses if needed), it may seem counter-intuitive but my motivation to restrict contributions (for now) is actually motivated by the intent to allow more people to use it.


