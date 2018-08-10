#ifndef BOOST_TMP_PUSH_BACK_HPP_INCLUDED
#define BOOST_TMP_PUSH_BACK_HPP_INCLUDED

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
		template <typename T, typename C = listify_>
		struct push_back_ {};
		namespace detail {
			template <unsigned N, typename T, typename C>
			struct dispatch<N, push_back_<T, C>> {
				template <typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<Ts...,
				                                                                             T>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif
