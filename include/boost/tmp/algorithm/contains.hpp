#ifndef BOOST_TMP_CONTAINS_HPP_INCLUDED
#define BOOST_TMP_CONTAINS_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "find_if.hpp"
#include "../identity.hpp"

namespace boost {
	namespace tmp {
		template <typename F, typename C = identity_>
		struct contains_ {};
	}
}

#endif