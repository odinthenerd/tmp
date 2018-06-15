#ifndef BOOST_TMP_EXPRESSION_HPP_INCLUDED
#define BOOST_TMP_EXPRESSION_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

namespace boost{
    namespace tmp {
        namespace detail{
            template<typename I, typename T, typename U>
            struct compose : T, U {
                compose(T t,U u):T{std::move(t)},U{std::move(u)}{}
            };
            template<typename I, typename U>
            struct exec_lambda{};
        }
    }
}
#endif
