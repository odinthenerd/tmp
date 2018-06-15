#ifndef BOOST_TMP_FILTER_HPP_INCLUDED
#define BOOST_TMP_FILTER_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../call.hpp"
#include "../detail/dispatch.hpp"
#include "../is.hpp"
#include "../pack.hpp"
#include "../sequence/fork.hpp"
#include "../sequence/index.hpp"
#include "../sequence/make_sequence.hpp"
#include "../sequence/zip_with_index.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename F, typename C = listify_>
		struct filter_ {
			template <typename CT>
			auto operator|(CT c) {
				static_assert(call_<is_<listify_>, C>::value,
				              "cannot add value continuation, type continuation already specified");
				return fusion::detail::make_expr<CT>{}(filter_<F, listify_>{}, std::move(c));
			}
		};

		namespace fusion {
			template <typename F, typename Tail>
			struct ast<filter_<F, listify_>, Tail> {
				filter_<F, listify_> head;
				Tail tail;
				template <typename... Is, typename... Ns, typename... Ts, typename... As>
				constexpr auto f(list_<list_<Ts...>, list_<Is...>, list_<Ns...>>, As &&... as) {
					auto p = fast_pack<detail::indexed_base<Ns, Ts>...>{static_cast<Ts>(as)...};
					return tail.f(typename Tail::template exec<typename Is::type...>{},
					              static_cast<typename Is::type>(static_cast<Is &>(p).data)...);
				};
				template <typename... Ts>
				using exec = call_<fork_<listify_, zip_with_index_<lift_<detail::indexed_base>,
				                                                   filter_<unpack_<i1_<F>>>>,
				                         size_<make_sequence_<>>, listify_>,
				                   Ts...>;
			};
			template <typename F>
			struct ast<filter_<F, listify_>, listify_> { // break recursion
				filter_<F, listify_> head;
				template <typename... Is, typename... Ns, typename... Ts>
				constexpr auto f(list_<list_<Is...>, list_<Ns...>>, Ts... as) {
					auto p = fast_pack<detail::indexed_base<Ns, Ts>...>{std::forward<Ts>(as)...};
					(void)p;
					return pack_(static_cast<Is &>(p).data...);
				};
				template <typename... Ts>
				using exec = call_<fork_<zip_with_index_<lift_<detail::indexed_base>,
				                                         filter_<unpack_<i1_<F>>>>,
				                         size_<make_sequence_<>>, listify_>,
				                   Ts...>;
			};

			template <typename F, typename C>
			struct rebind<filter_<F, C>> {
				using type = ast<filter_<F, listify_>, typename rebind<C>::type>;
			};

			template <typename F>
			struct rebind<filter_<F, listify_>> {
				using type = ast<filter_<F, listify_>, listify_>;
			};
		}

		namespace detail {

			template <unsigned N, template <typename...> class F, typename C>
			struct filtery;

			template <template <typename...> class F, typename C>
			struct filtery<0, F, C> {
				template <unsigned N, typename T, typename U, typename... Ts>
				using f = typename filtery<(F<U>::value + 2 * (N == 1)), F,
				                           C>::template f<(N - 1), U, Ts...>;
			};
			template <template <typename...> class F, typename C>
			struct filtery<1, F, C> {
				template <unsigned N, typename T, typename U, typename... Ts>
				using f = typename filtery<(F<U>::value + 2 * (N == 1)), F,
				                           C>::template f<(N - 1), U, Ts..., T>;
			};
			template <template <typename...> class F, typename C>
			struct filtery<2, F, C> {
				template <unsigned N, typename T, typename... Ts>
				using f = call_<C, Ts...>;
			};
			template <template <typename...> class F, typename C>
			struct filtery<3, F, C> {
				template <unsigned N, typename T, typename... Ts>
				using f = call_<C, Ts..., T>;
			};

			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, filter_<lift_<F>, C>> {
				template <typename T, typename... Ts>
				using f = typename filtery<(F<T>::value + 2 * (N == 1)), F,
				                           C>::template f<(sizeof...(Ts)), T, Ts...>;
			};

			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<0, filter_<lift_<F>, lift_<C>>> {
				template <typename... Ts>
				using f = C<>;
			};

			template <unsigned N, typename F, typename C>
			struct dispatch<N, filter_<F, C>> {
				template <typename T, typename... Ts>
				using f = typename filtery<(dispatch<1, F>::template f<T>::value + 2 * (N == 1)),
				                           dispatch<1, F>::template f,
				                           C>::template f<(sizeof...(Ts)), T, Ts...>;
			};

			template <typename F, typename C>
			struct dispatch<0, filter_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<0, C>::template f<>;
			};
		}
	}
}

#endif