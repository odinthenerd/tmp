#ifndef BOOST_TMP_COUNT_IF_HPP_INCLUDED
#define BOOST_TMP_COUNT_IF_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "transform.hpp"
#include "../call.hpp"
#include "../detail/dispatch.hpp"
#include "../if.hpp"
#include "../sequence/join.hpp"
#include "../sequence/size.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename F, typename C = identity_>
		struct count_if_ {};
		namespace detail {
			template <unsigned N, typename F, typename C>
			struct dispatch<N, count_if_<F, C>>
			    : dispatch<N, transform_<if_<F, always_<list_<void>>, always_<list_<>>>,
			                             join_<size_<C>>>> {};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif