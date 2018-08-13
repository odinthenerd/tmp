#ifndef BOOST_TMP_FIND_IF_HPP_INCLUDED
#define BOOST_TMP_FIND_IF_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../detail/capabilities.hpp"
#include "../fusion.hpp"
#include "../sequence/index.hpp"
#include "../sequence/size.hpp"
#include "../sequence/unpack.hpp"
#include "../vocabulary.hpp"
namespace boost {
	namespace tmp {
		template <typename F, typename C = identity_>
		struct find_if_ {};
#ifdef BOOST_TMP_CPP14
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
				        call_<fork_<zip_with_index_<lift_<detail::base>, find_if_<unpack_<i1_<F>>>>,
				                    size_<make_sequence_<>>, listify_>,
				              Ts...>;
			};
			template <typename F>
			struct ast<find_if_<F, identity_>, listify_> { // break recursion
				find_if_<F, identity_> head;
				template <typename... Bs> //not found case
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
				        list_<call_<fork_<find_if_<unpack_<i1_<F>>, lift_<index_, lift_<unpack_>>>,
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
		namespace detail {
			template <typename T>
			using id_ = T; // weird clang workaround
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
				return rest_size < 8 ? (rest_size == 0 ? 1000 : 1001) : 1008;
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
				        id_<typename F::template f<T0>::template f<T1>::template f<T2>::template f<
				                T3>::template f<T4>::template f<T5>::template f<T6>::
				                    template f<T7>>::value)>::template f<F, N + 8, Ts...>;
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
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif