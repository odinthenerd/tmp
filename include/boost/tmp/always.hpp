#ifndef BOOST_TMP_ALWAYS_HPP_INCLUDED
#define BOOST_TMP_ALWAYS_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "detail/dispatch.hpp"
#include "identity.hpp"

namespace boost {
	namespace tmp {
		template <typename T, typename C = identity_>
		struct always_ {};

		namespace detail {
			template <unsigned N, typename T, typename C>
			struct dispatch<N, always_<T, C>> {
				template <typename...>
				using f = typename dispatch<1, C>::template f<T>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost
#endif
