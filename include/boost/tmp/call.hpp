#ifndef BOOST_TMP_CALL_HPP_INCLUDED
#define BOOST_TMP_CALL_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <type_traits>
#include "detail/capabilities.hpp"
#include "detail/dispatch.hpp"
#include "vocabulary.hpp"

namespace boost {
	namespace tmp {
		namespace detail {
			template <bool B>
			struct maybe_test_impl {
				template <typename T>
				using f = T;
			};
			template <>
			struct maybe_test_impl<true> {};

			template <typename T>
			using maybe_impl =
			        typename maybe_test_impl<std::is_same<T, nothing_>::value>::template f<T>;

			template <typename F, typename... Ts> // workaround for old clang
			struct call_impl {
				using type = typename dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>;
			};
		} // namespace detail

#if defined(BOOST_TMP_CLANG_ARITY_BUG)
		template <typename T, typename... Ts>
		using call_ = typename detail::call_impl<T, Ts...>::type;
#else
		template <typename T, typename... Ts>
		using call_ = typename detail::dispatch<detail::find_dispatch(sizeof...(Ts)),
		                                        T>::template f<Ts...>;
#endif
		template <typename T, typename... Ts>
		using call_t = typename detail::dispatch<detail::find_dispatch(sizeof...(Ts)),
		                                         T>::template f<Ts...>::type;
#if defined(__cpp_variable_templates)
		template <typename T, typename... Ts>
		constexpr auto call_v =
		        detail::dispatch<detail::find_dispatch(sizeof...(Ts)), T>::template f<Ts...>::value;
#endif

		template <typename C = identity_>
		struct call_f_ {};

		namespace detail {
			template <unsigned N, typename C>
			struct dispatch<N, call_f_<C>> {
				template <typename F, typename... Ts>
				using f = typename dispatch<1, C>::template f<typename dispatch<
				        detail::find_dispatch(sizeof...(Ts)), F>::template f<Ts...>>;
			};
		} // namespace detail

		template <typename T, typename... Ts>
		using maybe_ =
		        detail::maybe_impl<typename detail::dispatch<detail::find_dispatch(sizeof...(Ts)),
		                                                     T>::template f<Ts...>>;

		template <typename T, typename... Ts>
		using maybe_t =
		        detail::maybe_impl<typename detail::dispatch<detail::find_dispatch(sizeof...(Ts)),
		                                                     T>::template f<Ts...>::type>;

#if defined(__cpp_variable_templates)
		template <typename T, typename... Ts>
		constexpr auto maybe_v =
		        detail::maybe_impl<typename detail::dispatch<detail::find_dispatch(sizeof...(Ts)),
		                                                     T>::template f<Ts...>>::value;
#endif
	} // namespace tmp
} // namespace boost
#endif
