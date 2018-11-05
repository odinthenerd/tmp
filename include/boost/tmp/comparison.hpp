#ifndef BOOST_TMP_COMPARISON_HPP_INCLUDED
#define BOOST_TMP_COMPARISON_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <type_traits>
#include "vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename P, typename C = identity_>
		struct is_ {};

		template <typename C = identity_>
		struct less_ {};

		namespace detail {
			template <typename P, typename C>
			struct dispatch<1, is_<P, C>> {
				template <typename T>
				using f = typename dispatch<1, C>::template f<bool_<std::is_same<P, T>::value>>;
			};

			template <typename C>
			struct dispatch<2, less_<C>> {
				template <typename T, typename U>
				using f = typename dispatch<1, C>::template f < bool_<T::value<U::value>>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost
#endif
