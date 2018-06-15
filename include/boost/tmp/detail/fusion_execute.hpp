#ifndef BOOST_TMP_FUSION_EXECUTE_HPP_INCLUDED
#define BOOST_TMP_FUSION_EXECUTE_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
#include "../vocabulary.hpp"

namespace boost{
    namespace tmp{
        namespace fusion{
            //T = type, this is the placeholder type, it will likely change for every operation step
            //I = indexer, when passed a pack will extract the correct element
            //As = actions, in other words the operation to be performed on the input
            template<typename T, typename I, typename...As>
            struct operation;

            namespace detail{
                template<typename T>
                struct do_operation;

                template<typename T, typename I>
                struct do_operation<operation<T,I>>
                {
                    template<typename...Ps, typename TR>
                    auto operator()(fast_pack<Ps...> p, TR tree){
                        return static_cast<I&>(p).data;
                    }
                };

                template<typename T, typename I, typename A>
                struct do_operation<operation<T,I,A>>
                {
                    template<typename...Ps, typename TR>
                    auto operator()(fast_pack<Ps...> p, TR tree){
                        return A{}(static_cast<I&>(p).data,tree);
                    }
                };
            };

            template<typename...Ts, typename In, typename OT>
            auto execute(list_<Ts...>,In pack, OT op_tree){
                return pack_(detail::do_operation<Ts>{}(pack,op_tree)...);
            };
        }
    }
}

#endif