#ifndef BOOST_TMP_MAKE_SEQUENCE_HPP_INCLUDED
#define BOOST_TMP_MAKE_SEQUENCE_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <utility>
#include "../call.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename F = identity_, typename C = listify_>
		struct make_sequence_ {};
		namespace detail {
			template <typename T>
			struct sequence_impl;

			template <std::size_t... Is>
			struct sequence_impl<std::index_sequence<Is...>> {
				template <typename F, typename C>
				using f = typename dispatch<find_dispatch(sizeof...(Is)), C>::template f<
				        typename dispatch<1, F>::template f<uint_<Is>>...>;
			};
			template <typename F, typename C>
			struct dispatch<1, make_sequence_<F, C>> {
				template <typename N>
				using f = typename sequence_impl<std::make_index_sequence<N::value>>::template f<F,
				                                                                                 C>;
			};
		}
	}
}

#endif
