#ifndef BOOST_TMP_IF_HPP_INCLUDED
#define BOOST_TMP_IF_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "vocabulary.hpp"

#if defined(__has_builtin)
#if __has_builtin(__type_pack_element)
#define BOOST_TMP_USE_TYPE_PACK_ELEMENT_INTRINSIC
#endif
#endif

namespace boost {
	namespace tmp {
		template <typename P, typename T, typename F = always_<nothing_>>
		struct if_ {};

		namespace detail {
			template <bool B>
			struct if_impl;

			template <>
			struct if_impl<true> {
				template <typename T, typename U>
				using f = T;
			};

			template <>
			struct if_impl<false> {
				template <typename T, typename U>
				using f = U;
			};

			template <typename P, typename T, typename F>
			struct dispatch<1, if_<P, T, F>> {
				template <typename T0>
				using f =
				        typename dispatch<1, typename if_impl<dispatch<1, P>::template f<
				                                     T0>::value>::template f<T, F>>::template f<T0>;
			};

			template <template <typename...> class P, typename T, typename F>
			struct dispatch<1, if_<lift_<P>, T, F>> {
				template <typename T0>
				using f = typename dispatch<
				        1, typename if_impl<P<T0>::value>::template f<T, F>>::template f<T0>;
			};

			template <unsigned N, typename P, typename T, typename F>
			struct dispatch<N, if_<P, T, F>> {
				template <typename... Ts>
				using f = typename dispatch<
				        find_dispatch(sizeof...(Ts)),
				        typename if_impl<dispatch<find_dispatch(sizeof...(Ts)), P>::template f<
				                Ts...>::value>::template f<T, F>>::template f<Ts...>;
			};
			template <unsigned N, template <typename...> class P, typename T, typename F>
			struct dispatch<N, if_<lift_<P>, T, F>> {
				template <typename... Ts>
				using f = typename dispatch<
				        find_dispatch(sizeof...(Ts)),
				        typename if_impl<P<Ts...>::value>::template f<T, F>>::template f<Ts...>;
			};
			template <template <typename...> class P>
			struct dispatch<1, if_<lift_<P>, listify_, always_<list_<>>>> {
				template <typename U>
#if defined(BOOST_TMP_USE_TYPE_PACK_ELEMENT_INTRINSIC)
				using f = __type_pack_element<(P<U>::value != 0), list_<U>, list_<>>;
#else
				using f = typename if_impl<P<U>::value>::template f<list_<U>, list_<>>;
#endif
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost
#endif
