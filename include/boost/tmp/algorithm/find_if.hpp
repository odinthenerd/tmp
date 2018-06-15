#ifndef BOOST_TMP_FIND_IF_HPP_INCLUDED
#define BOOST_TMP_FIND_IF_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename F, typename C = identity_>
		struct find_if_ {};

		namespace fusion {
			template <typename F, typename Tail>
			struct ast<find_if_<F, identity_>, Tail> {
				find_if_<F, identity_> head;
				Tail tail;
				template <typename... Is, typename... Ns, typename... Ts>
				constexpr auto f(list_<list_<Is...>, list_<Ns...>>, Ts... as) {
					auto p = fast_pack<detail::indexed_base<Ns, Ts>...>{std::forward<Ts>(as)...};
					return tail.f(typename Tail::template exec<typename Is::type...>{},
					              static_cast<Is &>(p).data...);
				};
				template <typename... Ts>
				using exec = call_<fork_<zip_with_index_<lift_<detail::indexed_base>,
				                                         find_if_<unpack_<i1_<F>>>>,
				                         size_<make_sequence_<>>, listify_>,
				                   Ts...>;
			};
			template <typename F>
			struct ast<find_if_<F, identity_>, listify_> { // break recursion
				find_if_<F, identity_> head;
				template <typename I, typename... Ns, typename... ATs, typename... Ts,
				          typename Ret = call_<index_<I>, ATs...>>
				constexpr auto f(list_<list_<ATs...>, I, list_<Ns...>>, Ts &&... as) -> Ret {
					auto p = fast_pack<detail::indexed_base<Ns, ATs>...>{static_cast<ATs>(as)...};
					(void)p;
					return static_cast<Ret>(static_cast<detail::indexed_base<I, Ret> &>(p).data);
				};
				template <typename... Ts>
				using exec = call_<fork_<listify_, // forwars the actual types
				                         find_if_<F>, size_<make_sequence_<>>, listify_>,
				                   Ts...>;
			};

			template <typename F, typename C>
			struct rebind<find_if_<F, C>> {
				using type = ast<find_if_<F, identity_>, typename rebind<C>::type>;
			};

			template <typename F>
			struct rebind<find_if_<F, identity_>> {
				using type = ast<find_if_<F, identity_>, listify_>;
			};
		}

		namespace detail {
			template <bool Found, int At, template <typename...> class F>
			struct county {
				static constexpr int value = -1;
				template <typename T>
				using f = county<F<T>::value, (At + 1), F>;
			};
			template <int At, template <typename...> class F>
			struct county<true, At, F> {
				template <typename T>
				using f                    = county;
				static constexpr int value = At;
			};

			constexpr unsigned select_foldey_loop(int rest_size) {
				return rest_size < 8 ? (rest_size == 0 ? 1000 : 1001) : rest_size < 32 ? 1008 :
				                                                                         1032;
			}
			constexpr unsigned select_foldey(int chunk_size, int rest_size, int found_at_index) {
				return found_at_index == -1 ? select_foldey_loop(rest_size) :
				                              chunk_size - found_at_index;
			}
			template <unsigned S>
			struct foldey {
				template <typename F, unsigned N, typename...>
				using f = uint_<N - S>;
			};
			template <>
			struct foldey<1000> {
				template <typename F, unsigned N, typename... Ts>
				using f = nothing_;
			};
			template <>
			struct foldey<1001> {
				template <typename F, unsigned N, typename T0, typename... Ts>
				using f = typename foldey<select_foldey(
				        1, sizeof...(Ts), F::template f<T0>::value)>::template f<F, N + 1, Ts...>;
			};
			template <>
			struct foldey<1008> {
				template <typename F, unsigned N, typename T0, typename T1, typename T2,
				          typename T3, typename T4, typename T5, typename T6, typename T7,
				          typename... Ts>
				using f = typename foldey<select_foldey(
				        8, sizeof...(Ts),
				        F::template f<T0>::template f<T1>::template f<T2>::template f<T3>::
				                template f<T4>::template f<T5>::template f<T6>::template f<
				                        T7>::value)>::template f<F, N + 8, Ts...>;
			};
			template <>
			struct foldey<1032> {
				template <typename F, unsigned N, typename T0, typename T1, typename T2,
				          typename T3, typename T4, typename T5, typename T6, typename T7,
				          typename T8, typename T9, typename T10, typename T11, typename T12,
				          typename T13, typename T14, typename T15, typename T16, typename T17,
				          typename T18, typename T19, typename T20, typename T21, typename T22,
				          typename T23, typename T24, typename T25, typename T26, typename T27,
				          typename T28, typename T29, typename T30, typename T31, typename... Ts>
				using f = typename foldey<select_foldey(
				        32, sizeof...(Ts),
				        F::template f<T0>::template f<T1>::template f<T2>::template f<
				                T3>::template f<T4>::template f<T5>::template f<T6>::
				                template f<T7>::template f<T8>::template f<T9>::template f<
				                        T10>::template f<T11>::template f<T12>::template f<T13>::
				                        template f<T14>::template f<T15>::template f<
				                                T16>::template f<T17>::template f<T18>::
				                                template f<T19>::template f<T20>::template f<
				                                        T21>::template f<T22>::template f<T23>::
				                                        template f<T24>::template f<
				                                                T25>::template f<T26>::
				                                                template f<T27>::template f<
				                                                        T28>::template f<T29>::
				                                                        template f<T30>::template f<
				                                                                T31>::value)>::
				        template f<F, N + 32, Ts...>;
			};

			template <unsigned N, typename F, typename C>
			struct dispatch<N, find_if_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<
				        typename foldey<(select_foldey_loop(sizeof...(Ts)))>::template f<
				                county<false, -1, dispatch<1, F>::template f>, 0, Ts...>>;
			};

			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, find_if_<lift_<F>, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<typename foldey<(select_foldey_loop(
				        sizeof...(Ts)))>::template f<county<false, -1, F>, 0, Ts...>>;
			};

		}
	}
}

#endif