#ifndef BOOST_TMP_PACK_HPP_INCLUDED
#define BOOST_TMP_PACK_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "detail/dispatch.hpp"
#include "lift.hpp"
#include "sequence/zip_with_index.hpp"

namespace boost{
    namespace tmp {
        namespace fusion{
            template<typename...Ts>
            struct fast_pack : Ts... {

                template<typename...As, typename = std::enable_if_t<(sizeof...(Ts) == sizeof...(As))>>
                fast_pack(As&&...args):Ts{std::forward<As>(args)}...{}
            };

            template<typename T>
            struct fast_pack<T> : T {
                template<typename A, typename = std::enable_if_t<(!
                        std::is_same<
                                std::remove_reference_t<
                                        std::remove_const_t<A>>,fast_pack<T>>::value)>>
                fast_pack(A&& arg):T{std::forward<A>(arg)}{}
            };

            template<>
            struct rebind<listify_>{
                using type = listify_;
            };

            namespace detail{
                template<typename I, typename T>
                struct indexed_base{
                    T data;
                };

                template<typename...Bs, typename P>
                auto pack_from_bases_r(list_<Bs...>,P&& p){
                    return fast_pack<Bs...>{static_cast<Bs&&>(p)...};
                };
                template<typename...Bs, typename P>
                auto pack_from_bases_l(list_<Bs...>,P& p){
                    return fast_pack<Bs...>{static_cast<Bs&>(p)...};
                };
            }
        }

        template<typename...Ts>
        auto pack_(Ts...args){
            return call_<zip_with_index_<
                    lift_<fusion::detail::indexed_base>,
                    lift_<fusion::fast_pack>>,
                    Ts...>{ std::move(args)... };
        }
    }
}
#endif
