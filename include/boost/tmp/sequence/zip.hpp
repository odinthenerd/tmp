#ifndef BOOST_TMP_ZIP_HPP_INCLUDED
#define BOOST_TMP_ZIP_HPP_INCLUDED

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
		template <typename F, typename C = listify_>
		struct zip_ {};
		namespace detail {
			template<typename F, typename C, typename T, typename U>
			struct zip2;
			template<typename F, typename C, typename...Ts, typename...Us>
			struct zip2<F,C,list_<Ts...>,list_<Us...>>{
				using type = typename dispatch<detail::find_dispatch(sizeof...(Ts)),C>::template f<typename dispatch<2,F>::template f<Ts,Us>...>;
			};
			template <typename F, typename C>
			struct dispatch<1, zip_<F, C>> : dispatch<1,unpack_<transform_<F,C>>> {};
			template <typename F, typename C>
			struct dispatch<2, zip_<F, C>> {
				template<typename T, typename U>
				using f = typename zip2<F,C,T,U>::type;
			};
		}
	} // namespace tmp
} // namespace boost

#endif
