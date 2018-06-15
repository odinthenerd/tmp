#ifndef BOOST_TMP_REMOVE_IF_HPP_INCLUDED
#define BOOST_TMP_REMOVE_IF_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "transform.hpp"
#include "../always.hpp"
#include "../call.hpp"
#include "../detail/dispatch.hpp"
#include "../if.hpp"
#include "../sequence/join.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename F, typename C = listify_>
		struct remove_if_ {};
		namespace detail {
			template <unsigned N, typename F, typename C>
			struct dispatch<N, remove_if_<F, C>>
			        : dispatch<N, transform_<if_<F, always_<list_<>>, listify_>, join_<C>>> {};
		}
	}
}

#endif