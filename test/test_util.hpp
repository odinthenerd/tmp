#ifndef BOOST_TMP_TEST_UTIL_HPP_INCLUDED
#define BOOST_TMP_TEST_UTIL_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../include/boost/tmp.hpp"

using namespace boost::tmp;
template <typename T>
using make_algo = fork_<always_<T>, identity_, call_f_<>>;

using extent = uint_<50>;

#endif
