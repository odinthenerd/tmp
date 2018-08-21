#ifndef BOOST_TMP_MAKE_SEQUENCE_HPP_INCLUDED
#define BOOST_TMP_MAKE_SEQUENCE_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <utility>
#include "unpack.hpp"
#include "../algorithm/transform.hpp"
#include "../call.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename F = identity_, typename C = listify_>
		struct make_sequence_ {};
		namespace detail {
			constexpr unsigned next_number(unsigned current, unsigned end) {
				return ((end - 2 * current) < 2) ?
				               end :
				               next_number(current,
				                           end / 2); // note that unsigned/2 always rounds down
			}

			constexpr unsigned next_state(unsigned current, unsigned end) {
				return ((end - current) < 2) ? end - current :
				                               (2 + (next_number(current, end) - 2 * current));
			}

			template <unsigned State>
			struct make_seq_impl;
			template <>
			struct make_seq_impl<0> { // done
				template <unsigned End, unsigned... Is>
				using f = list_<uint_<Is>...>;
			};
			template <>
			struct make_seq_impl<1> { // done +1
				template <unsigned End, unsigned... Is>
				using f = list_<uint_<Is>..., uint_<End - 1>>;
			};
			template <>
			struct make_seq_impl<2> { // double
				template <unsigned End, unsigned... Is>
				using f = typename make_seq_impl<next_state(
				        2 * sizeof...(Is), End)>::template f<End, Is..., (Is + sizeof...(Is))...>;
			};
			template <>
			struct make_seq_impl<3> { // double +1
				template <unsigned End, unsigned... Is>
				using f =
				        typename make_seq_impl<next_state(2 * sizeof...(Is) + 1, End)>::template f<
				                End, Is..., (Is + sizeof...(Is))..., (2 * sizeof...(Is))>;
			};

			template <typename F, typename C>
			struct dispatch<1, make_sequence_<F, C>> {
				template <typename N>
				using f = typename dispatch<1, unpack_<transform_<F, C>>>::template f<
				        typename make_seq_impl<next_state(0, N::value)>::template f<N::value>>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif
