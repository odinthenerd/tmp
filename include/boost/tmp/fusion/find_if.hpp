#ifndef BOOST_TMP_FUSION_FIND_IF_HPP_INCLUDED
#define BOOST_TMP_FUSION_FIND_IF_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../algorithm/find_if.hpp"
#include "../detail/capabilities.hpp"
#include "../fusion.hpp"
#include "../sequence/index.hpp"
#include "../sequence/size.hpp"
#include "../sequence/unpack.hpp"
namespace boost {
	namespace tmp {
#ifdef BOOST_TMP_CPP14
		template <typename F>
		struct find_if_<F, listify_> {
			template <typename CT>
			auto operator|(CT c) {
				return fusion::detail::make_expr<CT>{}(find_if_<F, listify_>{}, std::move(c));
			}
		};
		namespace fusion {
			template <typename F, typename Tail>
			struct ast<find_if_<F, identity_>, Tail> {
				find_if_<F, identity_> head;
				Tail tail;
				template <typename... Is, typename... Ns, typename... Ts>
				constexpr auto f(list_<list_<Is...>, list_<Ns...>>, Ts... as) {
					auto p = pack<detail::base<Ns, Ts>...>{std::forward<Ts>(as)...};
					return tail.f(typename Tail::template exec<typename Is::type...>{},
					              static_cast<Is &>(p).data...);
				};
				template <typename... Ts>
				using exec =
				        call_<tee_<zip_with_index_<lift_<detail::base>, find_if_<unpack_<i1_<F>>>>,
				                   size_<make_sequence_<>>, listify_>,
				              Ts...>;
			};
			template <typename F>
			struct ast<find_if_<F, identity_>, listify_> { // break recursion
				find_if_<F, identity_> head;
				template <typename... Bs> // not found case
				constexpr nothing_ f(list_<nothing_>, const pack<Bs...> &p) {
					return nothing_{};
				};
				template <typename T, typename... Bs>
				constexpr auto f(list_<T>, pack<Bs...> &p) -> typename T::type {
					return static_cast<T &>(p).get();
				};
				template <typename T, typename... Bs>
				constexpr auto f(list_<T>, const pack<Bs...> &p) -> typename T::type {
					return static_cast<const T &>(p).get();
				};
				template <typename T, typename... Bs>
				constexpr auto f(list_<T>, const pack<Bs...> &&p) -> typename T::type {
					return static_cast<const T &&>(p).get();
				};
				template <typename T, typename... Bs>
				constexpr auto f(list_<T>, pack<Bs...> &&p) -> typename T::type {
					return static_cast<T &&>(p).get();
				};
				template <typename... Ts>
				using exec =
				        list_<call_<tee_<find_if_<unpack_<i1_<F>>, lift_<index_, lift_<unpack_>>>,
				                         listify_, call_f_<>>,
				                    Ts...>>;
			};

			template <typename F, typename C>
			struct rebind<find_if_<F, C>> {
				using type = ast<find_if_<F, identity_>, typename rebind<C>::type>;
			};

			template <typename F>
			struct rebind<find_if_<F, identity_>> {
				using type = ast<find_if_<F, identity_>, listify_>;
			};
		} // namespace fusion
#endif
	} // namespace tmp
} // namespace boost

#endif