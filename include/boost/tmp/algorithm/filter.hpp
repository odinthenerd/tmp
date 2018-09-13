#ifndef BOOST_TMP_FILTER_HPP_INCLUDED
#define BOOST_TMP_FILTER_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../detail/capabilities.hpp"
#include "../detail/dispatch.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename F, typename C = listify_>
		struct filter_ {};

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
			struct filtery<2, F, C> { // all the way around, remove last
				template <unsigned N, typename T, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
			};
			template <template <typename...> class F, typename C>
			struct filtery<3, F, C> { // all the way around, keep last
				template <unsigned N, typename T, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<Ts...,
				                                                                             T>;
			};

			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, filter_<lift_<F>, C>> {
				template <typename T, typename... Ts>
				using f = typename filtery<(F<T>::value + 2 * (sizeof...(Ts) == 0)), F,
				                           C>::template f<(sizeof...(Ts)), T, Ts...>;
			};

			template <unsigned N, typename F, typename C>
			struct dispatch<N, filter_<F, C>> {
				template <typename T, typename... Ts>
				using f = typename filtery<
				        (dispatch<1, F>::template f<T>::value + 2 * (sizeof...(Ts) == 0)),
				        dispatch<1, F>::template f, C>::template f<(sizeof...(Ts)), T, Ts...>;
			};

			template <typename F, typename C>
			struct dispatch<0, filter_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<0, C>::template f<>;
			};
			template <template <typename...> class F, typename C>
			struct dispatch<0, filter_<lift_<F>, C>> {
				template <typename... Ts>
				using f = typename dispatch<0, C>::template f<>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif