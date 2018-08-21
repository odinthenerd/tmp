#ifndef BOOST_TMP_POP_FRONT_HPP_INCLUDED
#define BOOST_TMP_POP_FRONT_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../identity.hpp"
#include "../vocabulary.hpp"
namespace boost {
	namespace tmp {
		template <typename C = listify_>
		struct pop_front_ {};
		namespace detail {
			template <unsigned N, typename C>
			struct dispatch<N, pop_front_<C>> {
				template <typename T, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
			};
			template <typename C>
			struct dispatch<0, pop_front_<C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<nothing_>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif
