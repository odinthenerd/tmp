#ifndef BOOST_TMP_FILTER_HPP_INCLUDED
#define BOOST_TMP_FILTER_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../call.hpp"
#include "../vocabulary.hpp"
#include "../detail/dispatch.hpp"
#include "../sequence/join.hpp"
#include "../sequence/unpack.hpp"
#include "../sequence/at.hpp"
#include "../if.hpp"
#include "../is.hpp"
#include "../pack.hpp"
#include "../sequence/fork.hpp"
#include "../sequence/unpack.hpp"
#include "../sequence/size.hpp"
#include "../sequence/make_sequence.hpp"

namespace boost {
	namespace tmp {
        template <typename F, typename C = listify_>
        struct filter_{
			template<typename CT>
			auto operator |(CT c){
				static_assert(call_<is_<listify_>,C>::value,"cannot add value continuation, type continuation already specified");
				return fusion::detail::make_expr<CT>{}(filter_<F,listify_>{},std::move(c));
			}
        };

		namespace fusion{
			template<typename F, typename Tail>
			struct ast<filter_<F,listify_>,Tail>{
				filter_<F,listify_> head;
				Tail tail;
				template<typename...Is, typename...Ns, typename...Ts>
				auto f(list_<list_<Is...>,list_<Ns...>>, Ts...as){
					auto p = fast_pack<detail::indexed_base<Ns,Ts>...>{std::forward<Ts>(as)...};
					return tail.f(typename Tail::template exec<typename Is::type...>{}, static_cast<Is&>(p).data... );
				};
				template<typename...Ts>
				using exec = call_<fork_<zip_with_index_<lift_<detail::indexed_base>,filter_<unpack_<at1_<F>>>>,size_<make_sequence_<>>,listify_>,Ts...>;
			};
			template<typename F>
			struct ast<filter_<F,listify_>,listify_>{  //break recursion
				filter_<F,listify_> head;
				template<typename...Is, typename...Ns, typename...Ts>
				auto f(list_<list_<Is...>,list_<Ns...>>, Ts...as){
					auto p = fast_pack<detail::indexed_base<Ns,Ts>...>{std::forward<Ts>(as)...};
					return pack_(static_cast<Is&>(p).data... );
				};
				template<typename...Ts>
				using exec = call_<fork_<zip_with_index_<lift_<detail::indexed_base>,filter_<unpack_<at1_<F>>>>,size_<make_sequence_<>>,listify_>,Ts...>;
			};

			template<typename F, typename C>
			struct rebind<filter_<F,C>>{
				using type = ast<filter_<F,listify_>, typename rebind<C>::type>;
			};

			template<typename F>
			struct rebind<filter_<F,listify_>>{
				using type = ast<filter_<F,listify_>, listify_>;
			};
		}

		namespace detail {
			template<unsigned N, typename F, typename C>
			struct dispatch<N,filter_<F,C>>{
				template <typename... Ts>
				using f = typename dispatch<(N + (N>sizeof...(Ts))), join_<C>>::template f<typename dispatch<1,if_<F,listify_,always_<list_<>>>>::template f<Ts>...>;
			};
		}
	}
}


#endif