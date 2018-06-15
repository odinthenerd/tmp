#ifndef BOOST_TMP_ZIP_HPP_INCLUDED
#define BOOST_TMP_ZIP_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../call.hpp"
#include "../vocabulary.hpp"
#include<utility>

namespace boost{
    namespace tmp{
    	template<typename F, typename C = listify_>
    	struct zip_{};
		namespace detail{
			//TODO add impl
		}
    }
}

#endif

