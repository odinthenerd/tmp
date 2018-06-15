#ifndef BOOST_TMP_FUSION_HPP_INCLUDED
#define BOOST_TMP_FUSION_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
#include "detail/fusion_rebind.hpp"
#include "detail/fusion_execute.hpp"
#include "pack.hpp"
#include "sequence/fork.hpp"
namespace boost{
    namespace tmp{
        namespace fusion{
            //will SFINAE if there is no rebind specialization
            template<typename...Ps, typename F,
                    typename RF = typename rebind<F>::type>
            auto operator||(fast_pack<Ps...>&&p, F f){
                using ops = call_<RF,call_<fork_<unpack_<at1_<>>,identity_,lift_<operation>>,Ps>...>;
                return execute(ops{},p,f);
            };
            //will SFINAE if rhs can not be called with pack parameters
            template<typename...Ps, typename F>
            auto operator||(fast_pack<Ps...>&&p, F f)->decltype(f(static_cast<Ps&>(p).data...)){
                return f(static_cast<Ps&>(p).data...);
            };
        }
    }
}

#endif