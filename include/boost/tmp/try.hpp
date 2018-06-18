#ifndef BOOST_TMP_TRY_HPP_INCLUDED
#define BOOST_TMP_TRY_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "identity.hpp"
#include "detail/dispatch.hpp"
#include "vocabulary.hpp"
#include "always.hpp"
#include "sequence/unpack.hpp"

namespace boost{
    namespace tmp {

        template<typename C = identity_>
        struct try_{};

        namespace detail{
            template<typename C, typename L, typename = void>
            struct try_impl{
                using type = nothing_;
            };
            template<typename C, typename L>
            struct try_impl<C,L,call_<always_<void>,call_<unpack_<C>,L>>>{
                using type = call_<unpack_<C>,L>;
            };
            template<unsigned N, typename C>
            struct dispatch<N,try_<C>>{
                template<typename...Ts>
                using f = typename try_impl<C,list_<Ts...>,void>::type;
            };
        }
    }
}
#endif
