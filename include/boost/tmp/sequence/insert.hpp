#ifndef BOOST_TMP_INSERT_HPP_INCLUDED
#define BOOST_TMP_INSERT_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "drop.hpp"
#include "push_front.hpp"
#include "rotate.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename N = uint_<0>, typename V = nothing_, typename C = listify_>
		struct insert_ {};

		namespace detail {
			template <unsigned N, typename I, typename V, typename C>
			struct dispatch<N, insert_<I, V, C>> {
				template <typename... Ts>
				using f = typename dispatch<
				        N, rotate_<I, push_front_<V, rotate_<uint_<(sizeof...(Ts) - I::value - 1)>,
				                                             C>>>>::template f<Ts...>;
			};
			template <typename I, typename V, typename C>
			struct dispatch<0, insert_<I, V, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<V>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif