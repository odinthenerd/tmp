#ifndef BOOST_TMP_tee_HPP_INCLUDED
#define BOOST_TMP_tee_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "push_front.hpp"
#include "rotate.hpp"
#include "../detail/dispatch.hpp"
#include "../logic.hpp"
#include "../vocabulary.hpp"
namespace boost {
	namespace tmp {
		template <typename... Fs>
		struct tee_ {};
		namespace detail {
			template <typename N, typename L, typename C, typename... Fs>
			struct tee_impl {
				template <typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
				        typename dispatch<find_dispatch(sizeof...(Ts)), Fs>::template f<Ts...>...,
				        typename dispatch<find_dispatch(sizeof...(Ts)), L>::template f<Ts...>>;
			};
			// specialization for case where last closure is a forward
			template <unsigned N, typename C, typename... Fs>
			struct tee_impl<uint_<N>, identity_, C, Fs...> {
				template <typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Fs) + sizeof...(Ts)), C>::
				        template f<typename dispatch<find_dispatch(sizeof...(Ts)),
				                                     Fs>::template f<Ts...>...,
				                   Ts...>;
			};
			template <typename L, typename C, typename... Fs>
			struct tee_impl<uint_<1>, L, C, Fs...> {
				template <typename T0>
				using f = typename dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
				        typename dispatch<1, Fs>::template f<T0>...,
				        typename dispatch<1, L>::template f<T0>>;
			};
			// specialization for case where last closure is a forward
			template <typename C, typename... Fs>
			struct tee_impl<uint_<1>, identity_, C, Fs...> {
				template <typename T0>
				using f = typename dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
				        typename dispatch<1, Fs>::template f<T0>..., T0>;
			};
			template <typename L, typename C, typename... Fs>
			struct tee_impl<uint_<2>, L, C, Fs...> {
				template <typename T0, typename T1>
				using f = typename dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
				        typename dispatch<2, Fs>::template f<T0, T1>...,
				        typename dispatch<2, L>::template f<T0, T1>>;
			};
			// specialization for case where last closure is a forward
			template <typename C, typename... Fs>
			struct tee_impl<uint_<2>, identity_, C, Fs...> {
				template <typename T0, typename T1>
				using f = typename dispatch<find_dispatch(sizeof...(Fs) + 2), C>::template f<
				        typename dispatch<2, Fs>::template f<T0, T1>..., T0, T1>;
			};

			// in case the continuation is an and_

			template <bool b, typename C, typename... Fs>
			struct tee_and_impl;
			template <typename C, typename... Fs>
			struct tee_and_impl<false, C, Fs...> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<false_>;
			};
			template <typename C, typename... Fs>
			struct tee_and_impl<true, C, Fs...> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<true_>;
			};
			template <typename C, typename F, typename... Fs>
			struct tee_and_impl<true, C, F, Fs...> {
				template <typename... Ts>
				using f = typename tee_and_impl<
				        dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>::value, C,
				        Fs...>::template f<Ts...>;
			};
			template <bool b, typename C, typename... Fs>
			struct tee_and_impl_1;
			template <typename C, typename... Fs>
			struct tee_and_impl_1<false, C, Fs...> {
				template <typename T0>
				using f = typename dispatch<1, C>::template f<false_>;
			};
			template <typename C, typename... Fs>
			struct tee_and_impl_1<true, C, Fs...> {
				template <typename T0>
				using f1 = typename dispatch<1, C>::template f<true_>;
			};
			template <typename C, typename F, typename... Fs>
			struct tee_and_impl_1<true, C, F, Fs...> {
				template <typename T0>
				using f = typename tee_and_impl<dispatch<1, F>::template f<T0>::value, C,
				                                Fs...>::template f<T0>;
			};
			template <bool b, typename C, typename... Fs>
			struct tee_and_impl_2;
			template <typename C, typename... Fs>
			struct tee_and_impl_2<false, C, Fs...> {
				template <typename T0, typename T1>
				using f = typename dispatch<1, C>::template f<false_>;
			};
			template <typename C, typename... Fs>
			struct tee_and_impl_2<true, C, Fs...> {
				template <typename T0, typename T1>
				using f = typename dispatch<1, C>::template f<true_>;
			};
			template <typename C, typename F, typename... Fs>
			struct tee_and_impl_2<true, C, F, Fs...> {
				template <typename T0, typename T1>
				using f = typename tee_and_impl<dispatch<2, F>::template f<T0, T1>::value, C,
				                                Fs...>::template f<T0, T1>;
			};

			template <unsigned N, typename L, typename C, typename... Fs>
			struct tee_impl<uint_<N>, L, and_<identity_, C>, Fs...> : tee_and_impl<true, C, Fs..., L> {};
			template <typename L, typename C, typename... Fs>
			struct tee_impl<uint_<1>, L, and_<identity_, C>, Fs...>
					: tee_and_impl_1<true, C, Fs..., L> {};
			template <typename C, typename... Fs>
			struct tee_impl<uint_<1>, identity_, and_<identity_, C>, Fs...>
					: tee_and_impl_1<true, C, Fs..., identity_> {};
			template <typename L, typename C, typename... Fs>
			struct tee_impl<uint_<2>, L, and_<identity_, C>, Fs...>
					: tee_and_impl_2<true, C, Fs..., L> {};
			template <typename C, typename... Fs>
			struct tee_impl<uint_<2>, identity_, and_<identity_, C>, Fs...>
					: tee_and_impl_2<true, C, Fs..., identity_> {};

			// in case the continuation is an or_

			template <bool b, typename C, typename... Fs>
			struct tee_or_impl;
			template <typename C, typename... Fs>
			struct tee_or_impl<true, C, Fs...> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<true_>;
			};
			template <typename C, typename... Fs>
			struct tee_or_impl<false, C, Fs...> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<false_>;
			};
			template <typename C, typename F, typename... Fs>
			struct tee_or_impl<false, C, F, Fs...> {
				template <typename... Ts>
				using f = typename tee_or_impl<
				        dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>::value, C,
				        Fs...>::template f<Ts...>;
			};
			template <bool b, typename C, typename... Fs>
			struct tee_or_impl_1;
			template <typename C, typename... Fs>
			struct tee_or_impl_1<true, C, Fs...> {
				template <typename T0>
				using f = typename dispatch<1, C>::template f<true_>;
			};
			template <typename C, typename... Fs>
			struct tee_or_impl_1<false, C, Fs...> {
				template <typename T0>
				using f1 = typename dispatch<1, C>::template f<false_>;
			};
			template <typename C, typename F, typename... Fs>
			struct tee_or_impl_1<false, C, F, Fs...> {
				template <typename T0>
				using f = typename tee_or_impl<dispatch<1, F>::template f<T0>::value, C,
				                               Fs...>::template f<T0>;
			};
			template <bool b, typename C, typename... Fs>
			struct tee_or_impl_2;
			template <typename C, typename... Fs>
			struct tee_or_impl_2<true, C, Fs...> {
				template <typename T0, typename T1>
				using f = typename dispatch<1, C>::template f<true_>;
			};
			template <typename C, typename... Fs>
			struct tee_or_impl_2<false, C, Fs...> {
				template <typename T0, typename T1>
				using f = typename dispatch<1, C>::template f<false_>;
			};
			template <typename C, typename F, typename... Fs>
			struct tee_or_impl_2<false, C, F, Fs...> {
				template <typename T0, typename T1>
				using f = typename tee_or_impl<dispatch<2, F>::template f<T0, T1>::value, C,
				                               Fs...>::template f<T0, T1>;
			};

			template <typename N, typename L, typename C, typename... Fs>
			struct tee_impl<N, L, or_<identity_, C>, Fs...> : tee_or_impl<false, C, Fs..., L> {};
			template <typename L, typename C, typename... Fs>
			struct tee_impl<uint_<1>, L, or_<identity_, C>, Fs...>
					: tee_or_impl_1<false, C, Fs..., L> {};
			template <typename C, typename... Fs>
			struct tee_impl<uint_<1>, identity_, or_<identity_, C>, Fs...>
					: tee_or_impl_1<false, C, Fs..., identity_> {};
			template <typename L, typename C, typename... Fs>
			struct tee_impl<uint_<2>, L, or_<identity_, C>, Fs...>
					: tee_or_impl_2<false, C, Fs..., L> {};
			template <typename C, typename... Fs>
			struct tee_impl<uint_<2>, identity_, or_<identity_, C>, Fs...>
					: tee_or_impl_2<false, C, Fs..., identity_> {};

			template <unsigned N, typename F0, typename F1, typename... Fs>
			struct dispatch<N, tee_<F0, F1, Fs...>>
			    : dispatch<find_dispatch(sizeof...(Fs) + 2),
			               rotate_<uint_<sizeof...(Fs)>, push_front_<uint_<N>, lift_<tee_impl>>>>::
			              template f<F0, F1, Fs...> {};

		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif
