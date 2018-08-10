#ifndef BOOST_TMP_TAKE_HPP_INCLUDED
#define BOOST_TMP_TAKE_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "drop.hpp"
#include "rotate.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename N = uint_<0>, typename C = listify_>
		struct take_ {};

		namespace detail {
			template <unsigned N, typename P, typename C>
			struct dispatch<N, take_<P, C>> {
				template <typename... Ts>
				using f = typename dispatch<
				        (N + sizeof...(Ts) < 0),
				        rotate_<P, drop_<uint_<(sizeof...(Ts) - P::value)>, C>>>::template f<Ts...>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif