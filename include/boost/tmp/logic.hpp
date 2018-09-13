#ifndef BOOST_TMP_LOGIC_HPP_INCLUDED
#define BOOST_TMP_LOGIC_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <type_traits>
#include "algorithm/find_if.hpp"
#include "call.hpp"
#include "comparison.hpp"
#include "vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename C = identity_>
		struct not_ {};
		template <typename F = identity_, typename C = identity_>
		struct or_ {};
		template <typename F = identity_, typename C = identity_>
		struct and_ {};

		namespace detail {
			template <typename C>
			struct dispatch<1, not_<C>> {
				template <typename T>
				using f = typename dispatch<1, C>::template f<bool_<(!T::value)>>;
			};

			template <bool Short, template <typename...> class F>
			struct andy {
				template <typename T>
				using f                    = andy<(!F<T>::value), F>;
				static constexpr int value = -1;
			};
			template <template <typename...> class F>
			struct andy<true, F> {
				template <typename T>
				using f                    = andy;
				static constexpr int value = 1;
			};
			template <bool Short, template <typename...> class F>
			struct ory {
				template <typename T>
				using f                    = ory<F<T>::value, F>;
				static constexpr int value = -1;
			};
			template <template <typename...> class F>
			struct ory<true, F> {
				template <typename T>
				using f                    = ory;
				static constexpr int value = 1;
			};

			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, and_<lift_<F>, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<
				        call_<is_<nothing_>, typename foldey<(select_foldey_loop(sizeof...(
				                                     Ts)))>::template f<andy<false, F>, 0, Ts...>>>;
			};
			template <template <typename...> class F, typename C>
			struct dispatch<0, and_<lift_<F>, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<bool_<false>>;
			};
			template <unsigned N, typename F, typename C>
			struct dispatch<N, and_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<
				        call_<is_<nothing_>,
				              typename foldey<(select_foldey_loop(sizeof...(Ts)))>::template f<
				                      andy<false, dispatch<1, F>::template f>, 0, Ts...>>>;
			};
			template <typename F, typename C>
			struct dispatch<0, and_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<bool_<false>>;
			};

			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, or_<lift_<F>, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<
				        call_<is_<nothing_, not_<identity_>>,
				              typename foldey<(select_foldey_loop(
				                      sizeof...(Ts)))>::template f<ory<false, F>, 0, Ts...>>>;
			};
			template <template <typename...> class F, typename C>
			struct dispatch<0, or_<lift_<F>, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<bool_<false>>;
			};
			template <unsigned N, typename F, typename C>
			struct dispatch<N, or_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<
				        call_<is_<nothing_, not_<identity_>>,
				              typename foldey<(select_foldey_loop(sizeof...(Ts)))>::template f<
				                      ory<false, dispatch<1, F>::template f>, 0, Ts...>>>;
			};
			template <typename F, typename C>
			struct dispatch<0, or_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<bool_<false>>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost
#endif
