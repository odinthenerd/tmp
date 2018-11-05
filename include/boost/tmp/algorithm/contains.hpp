#ifndef BOOST_TMP_CONTAINS_HPP_INCLUDED
#define BOOST_TMP_CONTAINS_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../identity.hpp"
#include "../logic.hpp"

namespace boost {
	namespace tmp {
		template <typename V, typename C = identity_>
		struct contains_;

		namespace detail {
			template <unsigned N, typename V, typename C>
			struct dispatch<N, contains_<V, C>> : dispatch<N, or_<is_<V>, C>> {};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif