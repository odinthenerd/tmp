#ifndef BOOST_TMP_PARTITION_HPP_INCLUDED
#define BOOST_TMP_PARTITION_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "filter.hpp"
#include "remove_if.hpp"
#include "../call.hpp"
#include "../sequence/tee.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename F, typename C = listify_>
		struct partition_ {};

		namespace detail {
			template <unsigned N, typename F, typename C>
			struct dispatch<N, partition_<F, C>> : dispatch<N, tee_<filter_<F>, remove_if_<F>, C>> {
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif