#ifndef BOOST_TMP_SIZE_HPP_INCLUDED
#define BOOST_TMP_SIZE_HPP_INCLUDED

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
		template <typename C = identity_>
		struct size_ {};
		namespace detail {
			template <unsigned N, typename C>
			struct dispatch<N, size_<C>> {
				template <typename... Ls>
				using f = typename dispatch<1, C>::template f<uint_<sizeof...(Ls)>>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif
