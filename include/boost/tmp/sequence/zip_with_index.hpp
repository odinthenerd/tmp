#ifndef BOOST_TMP_ZIP_WITH_INDEX_HPP_INCLUDED
#define BOOST_TMP_ZIP_WITH_INDEX_HPP_INCLUDED

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
		template <typename F = listify_, typename C = listify_>
		struct zip_with_index_ {};
		namespace detail {
			template <unsigned N, typename T = std::make_index_sequence<N>>
			struct indexer;

			template <unsigned N, std::size_t... Is>
			struct indexer<N, std::index_sequence<Is...>> {
				template <template <typename...> class F, typename C, typename... Ts>
				using f = typename C::template f<F<uint_<Is>, Ts>...>;
			};

			template <unsigned N, typename F, typename C>
			struct dispatch<N, zip_with_index_<F, C>> {
				template <typename... Ts>
				using f = typename indexer<sizeof...(Ts)>::template f<dispatch<2, F>::template f,
				                                                      dispatch<N, C>, Ts...>;
			};
		}
	}
}

#endif
