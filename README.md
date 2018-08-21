
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
 
 ### Collaboration
I have heard from many developers who must roll their own metaprogramming library at work because their lawyers are afraid to use something open source. Whether or not this is merited is another question, but I have decided to retain full authorship of this library until I can get a Contributor License Agreement (CLA) worked out which is up to snuff. If you have knowledge in this field help would be much appreciated.
I would be very happy for bug reports. I will offer this library under the boost license indefinitely (and may offer it under other licenses if needed).
