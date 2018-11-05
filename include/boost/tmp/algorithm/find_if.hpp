#ifndef BOOST_TMP_FIND_IF_HPP_INCLUDED
#define BOOST_TMP_FIND_IF_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../detail/capabilities.hpp"
#include "../vocabulary.hpp"
namespace boost {
	namespace tmp {
		template <typename F, typename C = identity_>
		struct find_if_ {};
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

			template <>
			struct foldey<1000000> {};

			template <unsigned N, typename F, typename C>
			struct dispatch<N, find_if_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<
				        typename foldey<select_foldey_loop(sizeof...(Ts))>::template f<
				                county<false, -1, dispatch<1, F>::template f>, 0, Ts...>>;
			};

			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, find_if_<lift_<F>, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<typename foldey<select_foldey_loop(
				        sizeof...(Ts))>::template f<county<false, -1, F>, 0, Ts...>>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif