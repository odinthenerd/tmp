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
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<9, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0, typename T1, typename T2, typename T3,
				          typename T4, typename T5, typename T6, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1),
				                            fold_left_<lift_<F>, lift_<C>>>::
				        template f<F<F<F<F<F<F<F<In, T0>, T1>, T2>, T3>, T4>, T5>, T6>, Ts...>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<16, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0, typename T1, typename T2, typename T3,
				          typename T4, typename T5, typename T6, typename T7, typename T8,
				          typename T9, typename T10, typename T11, typename T12, typename T13,
				          typename T14, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1),
				                            fold_left_<lift_<F>, lift_<C>>>::
				        template f<
				                F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<In, T0>, T1>, T2>, T3>, T4>, T5>, T6>,
				                                T7>,
				                              T8>,
				                            T9>,
				                          T10>,
				                        T11>,
				                      T12>,
				                    T13>,
				                  T14>,
				                Ts...>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<17, fold_left_<lift_<F>, lift_<C>>>
			    : dispatch<16, fold_left_<lift_<F>, lift_<C>>> {};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<32, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0, typename T1, typename T2, typename T3,
				          typename T4, typename T5, typename T6, typename T7, typename T8,
				          typename T9, typename T10, typename T11, typename T12, typename T13,
				          typename T14, typename T15, typename T16, typename T17, typename T18,
				          typename T19, typename T20, typename T21, typename T22, typename T23,
				          typename T24, typename T25, typename T26, typename T27, typename T28,
				          typename T29, typename T30, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1),
				                            fold_left_<lift_<F>, lift_<C>>>::
				        template f<
				                F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<In, T0>,
				                                                                            T1>,
				                                                                          T2>,
				                                                                        T3>,
				                                                                      T4>,
				                                                                    T5>,
				                                                                  T6>,
				                                                                T7>,
				                                                              T8>,
				                                                            T9>,
				                                                          T10>,
				                                                        T11>,
				                                                      T12>,
				                                                    T13>,
				                                                  T14>,
				                                                T15>,
				                                              T16>,
				                                            T17>,
				                                          T18>,
				                                        T19>,
				                                      T20>,
				                                    T21>,
				                                  T22>,
				                                T23>,
				                              T24>,
				                            T25>,
				                          T26>,
				                        T27>,
				                      T28>,
				                    T29>,
				                  T30>,
				                Ts...>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<33, fold_left_<lift_<F>, lift_<C>>>
			    : dispatch<32, fold_left_<lift_<F>, lift_<C>>> {};
			template <template <typename...> class F, template <typename...> class C>
			struct dispatch<64, fold_left_<lift_<F>, lift_<C>>> {
				template <typename In, typename T0, typename T1,
						typename T2, typename T3, typename T4, typename T5, typename T6,
						typename T7, typename T8, typename T9, typename T10, typename T11,
						typename T12, typename T13, typename T14, typename T15, typename T16,
						typename T17, typename T18, typename T19, typename T20, typename T21,
						typename T22, typename T23, typename T24, typename T25, typename T26,
						typename T27, typename T28, typename T29, typename T30, typename T31,
						typename T32, typename T33, typename T34, typename T35, typename T36,
						typename T37, typename T38, typename T39, typename T40, typename T41,
						typename T42, typename T43, typename T44, typename T45, typename T46,
						typename T47, typename T48, typename T49, typename T50, typename T51,
						typename T52, typename T53, typename T54, typename T55, typename T56,
						typename T57, typename T58, typename T59, typename T60, typename T61,
						typename T62, typename T63, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1),
						fold_left_<lift_<F>, lift_<C>>>::
				template f<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<In, T0>,
						T1>,
						T2>,
						T3>,
						T4>,
						T5>,
						T6>,
						T7>,
						T8>,
						T9>,
						T10>,
						T11>,
						T12>,
						T13>,
						T14>,
						T15>,
						T16>,
						T17>,
						T18>,
						T19>,
						T20>,
						T21>,
						T22>,
						T23>,
						T24>,
						T25>,
						T26>,
						T27>,
						T28>,
						T29>,
						T30>,
						T31>,
						T32>,
						T33>,
						T34>,
						T35>,
						T36>,
						T37>,
						T38>,
						T39>,
						T40>,
						T41>,
						T42>,
						T43>,
						T44>,
						T45>,
						T46>,
						T47>,
						T48>,
						T49>,
						T50>,
						T51>,
						T52>,
						T53>,
						T54>,
						T55>,
						T56>,
						T57>,
						T58>,
						T59>,
						T60>,
						T61>,
						T62>,
						T63>,
						Ts...>;
			};
			template <unsigned N, template <typename...> class F, template <typename...> class C>
			struct dispatch<N, fold_left_<lift_<F>, lift_<C>>>
			    : dispatch<64, fold_left_<lift_<F>, lift_<C>>> {};

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