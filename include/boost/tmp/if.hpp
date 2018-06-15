#ifndef BOOST_TMP_IF_HPP_INCLUDED
#define BOOST_TMP_IF_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "vocabulary.hpp"

namespace boost{
    namespace tmp {
        template<typename P, typename T, typename F = always_<nothing_>>
        struct if_{};

        namespace detail{
            template <bool B>
            struct if_impl;

            template <>
            struct if_impl<true> {
                template<typename T, typename U>
                using f = T;
            };

            template <>
            struct if_impl<false>{
                template<typename T, typename U>
                using f = U;
            };

            template<unsigned N, typename P, typename T, typename F>
            struct dispatch<N,if_<P,T,F>>{
                template<typename...Ts>
                using f = typename dispatch<(N+(N>sizeof...(Ts))),typename if_impl<call_<P,Ts...>::value>::template f<T,F>>::template f<Ts...>;
            };
        }
    }
}
#endif
