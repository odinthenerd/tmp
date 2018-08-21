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
		/// fold left considers the first element in the input pack the initial state, use
		/// `push_front<>` to add initial state if needed
		template <typename F = listify_, typename C = identity_>
		struct fold_left_ {};
		namespace detail {
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<0, fold_left_<lift_<F>, lift_<C>>> {
				template <typename...>
				using f = nothing_;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<1, fold_left_<lift_<F>, lift_<C>>> {
				template <typename T>
				using f = C<T>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<2, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0>
				using f = C<F<In, T0>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<3, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0, typename T1>
				using f = C<F<F<In, T0>, T1>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<4, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0, typename T1, typename T2>
				using f = C<F<F<F<In, T0>, T1>, T2>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<5, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0, typename T1, typename T2, typename T3>
				using f = C<F<F<F<F<In, T0>, T1>, T2>, T3>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<6, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0, typename T1, typename T2, typename T3,
				          typename T4>
				using f = C<F<F<F<F<F<In, T0>, T1>, T2>, T3>, T4>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<7, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0, typename T1, typename T2, typename T3,
				          typename T4, typename T5>
				using f = C<F<F<F<F<F<F<In, T0>, T1>, T2>, T3>, T4>, T5>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<8, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0, typename T1, typename T2, typename T3,
				          typename T4, typename T5, typename T6>
				using f = C<F<F<F<F<F<F<F<In, T0>, T1>, T2>, T3>, T4>, T5>, T6>>;
			};
			template <unsigned N, template <typename...> class F, template <typename...> class C>
			struct dispatch<N, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0, typename T1, typename T2, typename T3,
				          typename T4, typename T5, typename T6, typename T7, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1),
				                            fold_left_<lift_<F>, lift_<C>>>::
				        template f<F<F<F<F<F<F<F<F<In, T0>, T1>, T2>, T3>, T4>, T5>, T6>, T7>,
				                   Ts...>;
			};
			template <unsigned N, typename F, typename C>
			struct dispatch<N, fold_left_<F, C>>
			    : dispatch<N, fold_left_<lift_<dispatch<2, F>::template f>,
			                             lift_<dispatch<1, C>::template f>>> {};
			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, fold_left_<lift_<F>, C>>
			    : dispatch<N, fold_left_<lift_<F>, lift_<dispatch<1, C>::template f>>> {};
			template <unsigned N, typename F, template <typename...> class C>
			struct dispatch<N, fold_left_<F, lift_<C>>>
			    : dispatch<N, fold_left_<lift_<dispatch<2, F>::template f>, lift_<C>>> {};

		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif