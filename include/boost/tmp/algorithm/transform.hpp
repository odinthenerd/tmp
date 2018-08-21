#ifndef BOOST_TMP_TRANSFORM_HPP_INCLUDED
#define BOOST_TMP_TRANSFORM_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../call.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename F = identity_, typename C = listify_>
		struct transform_ {};
		namespace detail {
			template <unsigned N, typename F, typename C>
			struct dispatch<N, transform_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts)), C>::template f<
				        typename dispatch<1, F>::template f<Ts>...>;
			};

			template <unsigned N, template <typename...> class F, typename FC, typename C>
			struct dispatch<N, transform_<lift_<F, FC>, C>> {
				template <typename... Ts>
				using f = typename dispatch<(N + (N > sizeof...(Ts))), C>::template f<F<Ts>...>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif
