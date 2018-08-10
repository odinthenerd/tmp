#ifndef BOOST_TMP_JOIN_HPP_INCLUDED
#define BOOST_TMP_JOIN_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../detail/dispatch.hpp"
#include "../sequence/unpack.hpp"
#include "../vocabulary.hpp"

namespace boost {
	namespace tmp {
		template <typename C = listify_>
		struct join_ {};
		namespace detail {
			template <template <typename...> class C, typename...>
			struct joiner;
			template <template <typename...> class C, typename... T0s, typename... T1s,
			          typename... T2s, typename... T3s, typename... T4s, typename... T5s,
			          typename... T6s, typename... T7s>
			struct joiner<C, list_<T0s...>, list_<T1s...>, list_<T2s...>, list_<T3s...>,
			              list_<T4s...>, list_<T5s...>, list_<T6s...>, list_<T7s...>> {
				template <typename... Vs>
				using f = C<T0s..., T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., Vs...>;
			};
			template <template <typename...> class C, typename... T0s, typename... T1s,
			          typename... T2s, typename... T3s, typename... T4s, typename... T5s,
			          typename... T6s, typename... T7s, typename... T8s, typename... T9s,
			          typename... T10s, typename... T11s, typename... T12s, typename... T13s,
			          typename... T14s, typename... T15s, typename... T16s, typename... T17s,
			          typename... T18s, typename... T19s, typename... T20s, typename... T21s,
			          typename... T22s, typename... T23s, typename... T24s, typename... T25s,
			          typename... T26s, typename... T27s, typename... T28s, typename... T29s,
			          typename... T30s, typename... T31s>
			struct joiner<C, list_<T0s...>, list_<T1s...>, list_<T2s...>, list_<T3s...>,
			              list_<T4s...>, list_<T5s...>, list_<T6s...>, list_<T7s...>, list_<T8s...>,
			              list_<T9s...>, list_<T10s...>, list_<T11s...>, list_<T12s...>,
			              list_<T13s...>, list_<T14s...>, list_<T15s...>, list_<T16s...>,
			              list_<T17s...>, list_<T18s...>, list_<T19s...>, list_<T20s...>,
			              list_<T21s...>, list_<T22s...>, list_<T23s...>, list_<T24s...>,
			              list_<T25s...>, list_<T26s...>, list_<T27s...>, list_<T28s...>,
			              list_<T29s...>, list_<T30s...>, list_<T31s...>> {
				template <typename... Vs>
				using f = C<T0s..., T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., T8s...,
				            T9s..., T10s..., T11s..., T12s..., T13s..., T14s..., T15s..., T16s...,
				            T17s..., T18s..., T19s..., T20s..., T21s..., T22s..., T23s..., T24s...,
				            T25s..., T26s..., T27s..., T28s..., T29s..., T30s..., T31s..., Vs...>;
			};
			template <unsigned N>
			struct join_loop;
			template <>
			struct join_loop<1> {
				template <template <typename...> class C, typename T0 = list_<>,
				          typename T1 = list_<>, typename T2 = list_<>, typename T3 = list_<>,
				          typename T4 = list_<>, typename T5 = list_<>, typename T6 = list_<>,
				          typename T7 = list_<>, typename T8 = list_<>, typename T9 = list_<>,
				          typename T10 = list_<>, typename T11 = list_<>, typename T12 = list_<>,
				          typename T13 = list_<>, typename T14 = list_<>, typename T15 = list_<>,
				          typename T16 = list_<>, typename T17 = list_<>, typename T18 = list_<>,
				          typename T19 = list_<>, typename T20 = list_<>, typename T21 = list_<>,
				          typename T22 = list_<>, typename T23 = list_<>, typename T24 = list_<>,
				          typename T25 = list_<>, typename T26 = list_<>, typename T27 = list_<>,
				          typename T28 = list_<>, typename T29 = list_<>, typename T30 = list_<>,
				          typename T31 = list_<>, typename... Ts>
				using f = typename join_loop<(sizeof...(Ts) > 8)>::template f<
				        joiner<C, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
				               T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
				               T29, T30, T31>::template f,
				        Ts...>;
			};
			template <>
			struct join_loop<0> {
				template <template <typename...> class C, typename T0 = list_<>,
				          typename T1 = list_<>, typename T2 = list_<>, typename T3 = list_<>,
				          typename T4 = list_<>, typename T5 = list_<>, typename T6 = list_<>,
				          typename T7 = list_<>, typename T8 = list_<>>
				using f = typename joiner<C, T0, T1, T2, T3, T4, T5, T6, T7>::template f<>;
			};
			template <unsigned N, template <typename...> class C>
			struct dispatch<N, join_<lift_<C>>> {
				template <typename... Ts>
				using f = typename join_loop<(sizeof...(Ts) > 8)>::template f<C, Ts...>;
			};

			template <unsigned N, typename C>
			struct dispatch<N, join_<C>> {
				template <typename... Ts>
				using f = typename join_loop<(
				        sizeof...(Ts) > 8)>::template f<dispatch_unknown<C>::template f, Ts...>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif
