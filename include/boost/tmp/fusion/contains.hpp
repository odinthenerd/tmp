#ifndef BOOST_TMP_FUSION_CONTAINS_HPP_INCLUDED
#define BOOST_TMP_FUSION_CONTAINS_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../algorithm/contains.hpp"
#include "../identity.hpp"
#include "../logic.hpp"

namespace boost {
	namespace tmp {
		template <typename V, typename C>
		struct contains_ {
#ifdef BOOST_TMP_CPP14
			template <typename CT>
			auto operator|(CT c) {
				static_assert(call_<is_<identity_>, C>::value,
				              "cannot add value continuation, type continuation already specified");
				return fusion::detail::make_expr<CT>{}(contains_<V, identity_>{}, std::move(c));
			}
#endif
		};

#ifdef BOOST_TMP_CPP14
		namespace fusion {
			template <typename V, typename Tail>
			struct ast<contains_<V, identity_>, Tail> {
				contains_<V, identity_> head;
				Tail tail;
				template <typename T, typename P>
				constexpr auto f(T, P) {
					return tail.f(typename Tail::template exec<T>{},
					              pack<detail::base<uint_<0>, T>>{{}});
				};
				template <typename... Ts>
				using exec = call_<or_<unpack_<i1_<is_<V>>>>, Ts...>;
			};
			template <typename V>
			struct ast<contains_<V, identity_>, listify_> { // break recursion
				contains_<V, listify_> head;

				template <typename T, typename P>
				constexpr auto f(T, P) {
					return pack<detail::base<uint_<0>, T>>{{}};
				};

				template <typename... Ts>
				using exec = call_<or_<unpack_<i1_<is_<V>>>>, Ts...>;
			};

			template <typename V, typename C>
			struct rebind<contains_<V, C>> {
				using type = ast<contains_<V, identity_>, typename rebind<C>::type>;
			};

			template <typename V>
			struct rebind<contains_<V, identity_>> {
				using type = ast<contains_<V, identity_>, listify_>;
			};
		} // namespace fusion
#endif
	} // namespace tmp
} // namespace boost

#endif