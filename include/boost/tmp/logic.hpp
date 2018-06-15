#ifndef BOOST_TMP_LOGIC_HPP_INCLUDED
#define BOOST_TMP_LOGIC_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "vocabulary.hpp"
#include <type_traits>

namespace boost{
    namespace tmp {
        template<typename C = identity_>
        struct not_{};
        template<typename C = identity_>
        struct or_{};

        namespace detail{
            template<typename C>
            struct dispatch<1,not_<C>>{
                template<typename T>
                using f = typename dispatch<1,C>::template f<bool_<(!T::value)>>;
            };


            template<typename C>
            struct dispatch<2,or_<C>>{
                template<typename T0, typename T1>
                using f = typename dispatch<1,C>::template f<bool_<(T0::value && T1::value)>>;
            };
        }
    }
}
#endif
