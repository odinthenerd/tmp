#ifndef BOOST_TMP_INDEX_HPP_INCLUDED
#define BOOST_TMP_INDEX_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../identity.hpp"
#include "../vocabulary.hpp"
namespace boost {
	namespace tmp {
		template <typename I, typename C = identity_>
		struct index_ {};
		template <typename C = identity_>
		using front_         = index_<uint_<0>, C>;

		template <typename C = identity_>
		using i0_            = index_<uint_<0>, C>;
		template <typename C = identity_>
		using i1_            = index_<uint_<1>, C>;
		template <typename C = identity_>
		using i2_            = index_<uint_<2>, C>;
		template <typename C = identity_>
		using i3_            = index_<uint_<3>, C>;
		template <typename C = identity_>
		using i4_            = index_<uint_<4>, C>;
		template <typename C = identity_>
		using i5_            = index_<uint_<5>, C>;
		template <typename C = identity_>
		using i6_            = index_<uint_<6>, C>;
		template <typename C = identity_>
		using i7_            = index_<uint_<7>, C>;
		namespace detail {
			template <unsigned N, typename I, typename C>
			struct dispatch<N, index_<I, C>> : dispatch<N, index_<uint_<I::value>, C>> {};
			template <unsigned N, typename C>
			struct dispatch<N, index_<uint_<0>, C>> {
				template <typename T0, typename... Ts>
				using f = typename dispatch<1, C>::template f<T0>;
			};
			template <unsigned N, typename C>
			struct dispatch<N, index_<uint_<1>, C>> {
				template <typename T0, typename T1, typename... Ts>
				using f = typename dispatch<1, C>::template f<T1>;
			};
			template <unsigned N, typename C>
			struct dispatch<N, index_<uint_<2>, C>> {
				template <typename T0, typename T1, typename T2, typename... Ts>
				using f = typename dispatch<1, C>::template f<T2>;
			};
			template <unsigned N, typename C>
			struct dispatch<N, index_<uint_<3>, C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
				using f = typename dispatch<1, C>::template f<T3>;
			};
			template <unsigned N, typename C>
			struct dispatch<N, index_<uint_<4>, C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename... Ts>
				using f = typename dispatch<1, C>::template f<T4>;
			};
			template <unsigned N, typename C>
			struct dispatch<N, index_<uint_<5>, C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename... Ts>
				using f = typename dispatch<1, C>::template f<T5>;
			};
			template <unsigned N, typename C>
			struct dispatch<N, index_<uint_<6>, C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename... Ts>
				using f = typename dispatch<1, C>::template f<T6>;
			};
			template <unsigned N, typename C>
			struct dispatch<N, index_<uint_<7>, C>> {
				template <typename T0, typename T1, typename T2, typename T3, typename T4,
				          typename T5, typename T6, typename T7, typename... Ts>
				using f = typename dispatch<1, C>::template f<T7>;
			};
		}
	}
}

#endif