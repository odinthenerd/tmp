#ifndef BOOST_TMP_FOLD_LEFT_HPP_INCLUDED
#define BOOST_TMP_FOLD_LEFT_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../call.hpp"
#include "../detail/dispatch.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		/// \brief folds left over a list using a binary predicate /
		/// fold left considers the first element in the input pack the state, use `push_front<>`
		/// to add state if needed
		template <typename F = listify_, typename C = identity_>
		struct fold_left_ {};
		namespace detail {
#define F_(L, R) typename dispatch<2, F>::template f<L, R>

			template <typename F, typename C>
			struct dispatch<1, fold_left_<F, C>> : dispatch<1, C> {};
			template <typename F, typename C>
			struct dispatch<2, fold_left_<F, C>> {
				template <typename In, typename T0>
				using f = typename dispatch<1, C>::template f<F_(In, T0)>;
			};
			template <typename F, typename C>
			struct dispatch<3, fold_left_<F, C>> {
				template <typename In, typename T0, typename T1>
				using f = typename dispatch<1, C>::template f<F_(F_(In, T0), T1)>;
			};
			template <typename F, typename C>
			struct dispatch<4, fold_left_<F, C>> {
				template <typename In, typename T0, typename T1, typename T2>
				using f = typename dispatch<1, C>::template f<F_(F_(F_(In, T0), T1), T2)>;
			};
			template <unsigned N, typename F, typename C>
			struct dispatch<N, fold_left_<F, C>> {
				template <typename In, typename T0, typename T1, typename T2, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts)), fold_left_<F, C>>::
				        template f<F_(F_(F_(In, T0), T1), T2), Ts...>;
			};

#undef F_
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif