#ifndef BOOST_TMP_REVERSE_HPP_INCLUDED
#define BOOST_TMP_REVERSE_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename C = listify_>
		struct reverse_ {};

		namespace detail {
			template <typename C, typename... Ts>
			struct reverse_impl {
				template <typename... Us>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + sizeof...(Us)),
				                            C>::template f<Ts..., Us...>;
			};

			template <typename C>
			struct dispatch<0, reverse_<C>> {
				template <typename...>
				using f = typename dispatch<0, C>::template f<>;
			};

			template <typename C>
			struct dispatch<1, reverse_<C>> {
				template <typename T>
				using f = typename dispatch<1, C>::template f<T>;
			};

			template <typename C>
			struct dispatch<2, reverse_<C>> {
				template <typename T0, typename T1>
				using f = typename dispatch<2, C>::template f<T1, T0>;
			};

			template <typename C>
			struct dispatch<3, reverse_<C>> {
				template <typename T0, typename T1, typename T2>
				using f = typename dispatch<3, C>::template f<T2, T1, T0>;
			};
			template <typename C>
			struct dispatch<4, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3>
				using f = typename dispatch<4, C>::template f<T3, T2, T1, T0>;
			};
			template <typename C>
			struct dispatch<5, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4>
				using f = typename dispatch<5, C>::template f<T4, T3, T2, T1, T0>;
			};
			template <typename C>
			struct dispatch<6, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5>
				using f = typename dispatch<6, C>::template f<T5, T4, T3, T2, T1, T0>;
			};
			template <typename C>
			struct dispatch<7, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6>
				using f = typename dispatch<7, C>::template f<T6, T5, T4, T3, T2, T1, T0>;
			};
			template <typename C>
			struct dispatch<8, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename T7>
				using f = typename dispatch<8, C>::template f<T7, T6, T5, T4, T3, T2, T1, T0>;
			};
			template <typename C>
			struct dispatch<9, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename T7, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1),
				                            reverse_<lift_<reverse_impl>>>::template f<Ts..., C>::
				        template f<T7, T6, T5, T4, T3, T2, T1, T0>;
			};
			template <typename C>
			struct dispatch<16, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename T7, typename T8, typename T9,
				          typename T10, typename T11, typename T12, typename T13, typename T14,
				          typename T15>
				using f = typename dispatch<16, C>::template f<T15, T14, T13, T12, T11, T10, T9, T8,
				                                               T7, T6, T5, T4, T3, T2, T1, T0>;
			};
			template <typename C>
			struct dispatch<17, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename T7, typename T8, typename T9,
				          typename T10, typename T11, typename T12, typename T13, typename T14,
				          typename T15, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1),
				                            reverse_<lift_<reverse_impl>>>::template f<Ts..., C>::
				        template f<T15, T14, T13, T12, T11, T10, T9, T8, T7, T6, T5, T4, T3, T2, T1,
				                   T0>;
			};
			template <typename C>
			struct dispatch<32, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename T7, typename T8, typename T9,
				          typename T10, typename T11, typename T12, typename T13, typename T14,
				          typename T15, typename T16, typename T17, typename T18, typename T19,
				          typename T20, typename T21, typename T22, typename T23, typename T24,
				          typename T25, typename T26, typename T27, typename T28, typename T29,
				          typename T30, typename T31>
				using f = typename dispatch<32, C>::template f<
				        T31, T30, T29, T28, T27, T26, T25, T24, T23, T22, T21, T20, T19, T18, T17,
				        T16, T15, T14, T13, T12, T11, T10, T9, T8, T7, T6, T5, T4, T3, T2, T1, T0>;
			};
			template <typename C>
			struct dispatch<33, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename T7, typename T8, typename T9,
				          typename T10, typename T11, typename T12, typename T13, typename T14,
				          typename T15, typename T16, typename T17, typename T18, typename T19,
				          typename T20, typename T21, typename T22, typename T23, typename T24,
				          typename T25, typename T26, typename T27, typename T28, typename T29,
				          typename T30, typename T31, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1),
				                            reverse_<lift_<reverse_impl>>>::template f<Ts..., C>::
				        template f<T31, T30, T29, T28, T27, T26, T25, T24, T23, T22, T21, T20, T19,
				                   T18, T17, T16, T15, T14, T13, T12, T11, T10, T9, T8, T7, T6, T5,
				                   T4, T3, T2, T1, T0>;
			};
			template <typename C>
			struct dispatch<64, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename T7, typename T8, typename T9,
				          typename T10, typename T11, typename T12, typename T13, typename T14,
				          typename T15, typename T16, typename T17, typename T18, typename T19,
				          typename T20, typename T21, typename T22, typename T23, typename T24,
				          typename T25, typename T26, typename T27, typename T28, typename T29,
				          typename T30, typename T31, typename T32, typename T33, typename T34,
				          typename T35, typename T36, typename T37, typename T38, typename T39,
				          typename T40, typename T41, typename T42, typename T43, typename T44,
				          typename T45, typename T46, typename T47, typename T48, typename T49,
				          typename T50, typename T51, typename T52, typename T53, typename T54,
				          typename T55, typename T56, typename T57, typename T58, typename T59,
				          typename T60, typename T61, typename T62, typename T63>
				using f = typename dispatch<16, C>::template f<
				        T63, T62, T61, T60, T59, T58, T57, T56, T55, T54, T53, T52, T51, T50, T49,
				        T48, T47, T46, T45, T44, T43, T42, T41, T40, T39, T38, T37, T36, T35, T34,
				        T33, T32, T31, T30, T29, T28, T27, T26, T25, T24, T23, T22, T21, T20, T19,
				        T18, T17, T16, T15, T14, T13, T12, T11, T10, T9, T8, T7, T6, T5, T4, T3, T2,
				        T1, T0>;
			};
			template <typename C>
			struct dispatch<65, reverse_<C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename T7, typename T8, typename T9,
				          typename T10, typename T11, typename T12, typename T13, typename T14,
				          typename T15, typename T16, typename T17, typename T18, typename T19,
				          typename T20, typename T21, typename T22, typename T23, typename T24,
				          typename T25, typename T26, typename T27, typename T28, typename T29,
				          typename T30, typename T31, typename T32, typename T33, typename T34,
				          typename T35, typename T36, typename T37, typename T38, typename T39,
				          typename T40, typename T41, typename T42, typename T43, typename T44,
				          typename T45, typename T46, typename T47, typename T48, typename T49,
				          typename T50, typename T51, typename T52, typename T53, typename T54,
				          typename T55, typename T56, typename T57, typename T58, typename T59,
				          typename T60, typename T61, typename T62, typename T63, typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1),
				                            reverse_<lift_<reverse_impl>>>::template f<Ts..., C>::
				        template f<T63, T62, T61, T60, T59, T58, T57, T56, T55, T54, T53, T52, T51,
				                   T50, T49, T48, T47, T46, T45, T44, T43, T42, T41, T40, T39, T38,
				                   T37, T36, T35, T34, T33, T32, T31, T30, T29, T28, T27, T26, T25,
				                   T24, T23, T22, T21, T20, T19, T18, T17, T16, T15, T14, T13, T12,
				                   T11, T10, T9, T8, T7, T6, T5, T4, T3, T2, T1, T0>;
			};
			template <unsigned N, typename C>
			struct dispatch<N, reverse_<C>> : dispatch<65, reverse_<C>> {};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif