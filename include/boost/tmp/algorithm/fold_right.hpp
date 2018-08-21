#ifndef BOOST_TMP_FOLD_RIGHT_HPP_INCLUDED
#define BOOST_TMP_FOLD_RIGHT_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <utility>

#include "../call.hpp"
#include "../detail/dispatch.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		/// \breif fold right considers the last element in the input pack the initial state, use
		/// push_back to add initial state if needed
		template <typename F, typename C = identity_>
		struct fold_right_ {};

		namespace detail {

			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<0, fold_right_<lift_<F>, lift_<C>>> {
				template <typename...>
				using f = nothing_;
			};

			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<1, fold_right_<lift_<F>, lift_<C>>> {
				template <typename T>
				using f = C<T>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<2, fold_right_<lift_<F>, lift_<C>>> {
				template <typename T0, typename In>
				using f = C<F<In, T0>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<3, fold_right_<lift_<F>, lift_<C>>> {
				template <typename T0, typename T1, typename In>
				using f = C<F<F<In, T1>, T0>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<4, fold_right_<lift_<F>, lift_<C>>> {
				template <typename T0, typename T1, typename T2, typename In>
				using f = C<F<F<F<In, T2>, T1>, T0>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<5, fold_right_<lift_<F>, lift_<C>>> {
				template <typename T0, typename T1, typename T2, typename T3, typename In>
				using f = C<F<F<F<F<In, T3>, T2>, T1>, T0>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<6, fold_right_<lift_<F>, lift_<C>>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename In>
				using f = C<F<F<F<F<F<In, T4>, T3>, T2>, T1>, T0>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<7, fold_right_<lift_<F>, lift_<C>>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename In>
				using f = C<F<F<F<F<F<F<In, T5>, T4>, T3>, T2>, T1>, T0>>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<8, fold_right_<lift_<F>, lift_<C>>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename In>
				using f = C<F<F<F<F<F<F<F<In, T6>, T5>, T4>, T3>, T2>, T1>, T0>>;
			};
			template <unsigned N, template <typename...> class F, template <typename...> class C>
			struct dispatch<N, fold_right_<lift_<F>, lift_<C>>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename T7, typename T8, typename... Ts>
				using f = C<F<F<F<F<F<F<F<F<F<typename dispatch<find_dispatch(sizeof...(Ts)),
				                                                fold_right_<lift_<F>, identity_>>::
				                                      template f<Ts...>,
				                              T8>,
				                            T7>,
				                          T6>,
				                        T5>,
				                      T4>,
				                    T3>,
				                  T2>,
				                T1>,
				              T0>>;
			};
			template <unsigned N, typename F, typename C>
			struct dispatch<N, fold_right_<F, C>>
			    : dispatch<N, fold_right_<lift_<dispatch<2, F>::template f>,
			                              lift_<dispatch<1, C>::template f>>> {};
			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, fold_right_<lift_<F>, C>>
			    : dispatch<N, fold_right_<lift_<F>, lift_<dispatch<1, C>::template f>>> {};
			template <unsigned N, typename F, template <typename...> class C>
			struct dispatch<N, fold_right_<F, lift_<C>>>
			    : dispatch<N, fold_right_<lift_<dispatch<2, F>::template f>, lift_<C>>> {};
		} // namespace detail
	} // namespace tmp
} // namespace boost
#endif
