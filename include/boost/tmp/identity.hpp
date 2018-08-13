#ifndef BOOST_TMP_IDENTITY_HPP_INCLUDED
#define BOOST_TMP_IDENTITY_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "detail/capabilities.hpp"
#include "detail/dispatch.hpp"
#include "detail/fusion_rebind.hpp"
namespace boost {
	namespace tmp {
		struct identity_ {};
#ifdef BOOST_TMP_CPP14
		namespace fusion {
			template <>
			struct rebind<identity_> {
				using type = identity_;
			};
		} // namespace fusion
#endif
		namespace detail {
			template <>
			struct dispatch<1, identity_> {
				template <typename T>
				using f = T;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost
#endif
