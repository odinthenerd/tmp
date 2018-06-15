#ifndef BOOST_TMP_REPLACE_IF_HPP_INCLUDED
#define BOOST_TMP_REPLACE_IF_HPP_INCLUDED

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
		template <typename Input, typename F, typename C = listify_>
		struct replace_if_ {};
		namespace detail {
			template <unsigned N, typename Input, typename F, typename C>
			struct dispatch<N, replace_if_<Input, F, C>>
			        : dispatch<N, transform_<if_<F, always_<Input>, identity_>, C>> {};
		}
	}
}

#endif