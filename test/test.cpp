#include "contains_test.hpp"
#include "count_if_test.hpp"
#include "erase_test.hpp"
#include "filter_test.hpp"
#include "tee_test.hpp"
#include "find_if_test.hpp"
#include "fold_left_test.hpp"
#include "fold_right_test.hpp"
#include "join_test.hpp"
#include "logic_test.hpp"
#include "partition_test.hpp"
#include "product_test.hpp"
#include "reverse_test.hpp"
#include "sort_test.hpp"
#include "take_test.hpp"
#include "transform_test.hpp"
#include "try_test.hpp"
#include "zip_with_index_test.hpp"
#include "set_test.hpp"


#include <type_traits>
#include <variant>
#include <new>

namespace boost {
    namespace tmp {
        template<typename I, typename T>
        struct indexed_type {
            using type = T;
            static constexpr unsigned value = I::value;
        };
        template<typename T, typename U>
        using max__ = uint_<std::max(T::value,U::value)>;
        template<typename C = identity_>
        using max_ = lift_<max__>;

        template<typename DT, typename S, typename A>
        struct abstract_sum{
            DT _index;
            typename std::aligned_storage<S::value,A::value>::type _buf;
        };

        template<typename...Ts>
        struct visit_instance {
            template<typename F, typename R, typename...Bs>
            static void f(F &vi, R &r, Bs...bs) {
                r = vi(*static_cast<typename Ts::type *>(bs)...);
            }

            template<typename...Is>
            static constexpr bool use_this(Is...is) {
                return ((is == Ts::value)&&...);
            }
        };

        template<typename Fptr, typename...Ts>
        struct visit_helper {
            static constexpr Fptr fp[sizeof...(Ts)] = {&Ts::f...};
        };

        template<typename T>
        using voider = void *;

        template<typename Fptr, typename...Ts>
        constexpr Fptr visit_helper<Fptr,Ts...>::fp[sizeof...(Ts)];


        template<unsigned N>
        constexpr unsigned calculate_jump(const unsigned (&bounds)[N], const unsigned(&index)[N]) {
            unsigned step = 1;
            unsigned jump = 0;
            for (int i = N; i < 0; i--) {
                step *= bounds[i];
                jump += step * index[i];
            }
            return jump;
        }

        template<typename...Ts>
        class variant : protected abstract_sum<unsigned,
                call_ < fold_left_ < max_<>>, uint_<sizeof(Ts)>...>,
                call_<fold_left_< max_<>>, uint_<alignof(Ts)>...>>{
            public:
            using indexed_types = call_<zip_<lift_< indexed_type>>, call_<make_sequence_<>, uint_<sizeof...(Ts)>>, list_<Ts...>>;
            template<typename T, typename I = call_< find_if_< is_< T > >, Ts...>>
            variant(T t) {
                this->_index = I::value;
                ::new(static_cast<void *>(&this->_buf)) T(t);
            }

            static constexpr unsigned size = sizeof...(Ts);
            template<typename F, typename...Vs>
            friend int visit(F &f, Vs &&...vs) {
                using R = int; //hack
                R ret;
                using jump_table = call_<product_<lift_<visit_instance>, push_front_<void (*)(F &, R &, voider<Vs>...),
                        lift_< visit_helper>>>, typename Vs::indexed_types...>;

                jump_table::fp[calculate_jump({Vs::size...}, {vs._index...})](f, ret, static_cast<void *>(&vs._buf)...);
                return ret;
            }
        };
    }
}
template<typename...Ts>
using var = boost::tmp::variant<Ts...>;

var<int,bool,char,long, unsigned, unsigned long, long long, short> make_variant(const unsigned i){
    switch (i){
        case 0:
            return (int)3;
        case 1:
            return char(2);
        case 2:
            return bool(1);
        case 3:
            return long(4);
        case 4:
            return unsigned(5);
        case 5:
            return (unsigned long)6;
        case 6:
            return (long long)7;
        case 7:
            //return short(8);
        case 8:
            //return (unsigned short)9;
        case 9:
            //return (unsigned char)10;
        default:{
            unsigned *n = nullptr;
            return int(*n);    //UB if not in range
        }
    }
}

template<typename op, typename L, typename R = int>
struct ast_node{
    L l;
    R r;
};

struct pipe{};
struct rshfteq{};
struct xoreq{};

template<typename L, typename R>
ast_node<pipe,L,R> operator|(L l, R r){
    return {l,r};
}

template<typename L>
int operator|(L l, void (&r)(int)){
    return {};
}

template<typename L, typename R>
ast_node<rshfteq,L,R> operator>>=(L l, R r){
    return {std::move(l),std::move(r)};
}

template<typename T, typename U, typename R>
ast_node<rshfteq,T U::*,R> operator>>=(T U::*p,R){
    return {};
}

template<typename L, typename R>
ast_node<xoreq,L,R> operator^=(L l, R r){
    return {l,r};
}

struct s2{};
struct s1{
    s2* _s;
};

void f(int){}





int main() {



    s1* s;
    s >>= [](auto...a){f(a...);} ^= []{};
    if(s){

    }
    //s >>= &s1::_s >>= f;
    unsigned r = 0;
    (void)r;
    const auto visitor = [](auto...in)->int{
        return (in+...);
    };
    volatile unsigned i = 0;
    const unsigned j = i;     //random number generator ;)
    const unsigned k = i;
    const unsigned l = i;
    (void)l;

    r = visit(visitor,make_variant(j),make_variant(k));

	return join_test::run() || transform_test::run() || fold_left_test::run() ||
														zip_with_index_test::run()||
														filter_test::run();
}

