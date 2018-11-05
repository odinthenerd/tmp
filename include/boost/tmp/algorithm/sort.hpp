#ifndef BOOST_TMP_SORT_HPP_INCLUDED
#define BOOST_TMP_SORT_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../comparison.hpp"
#include "../detail/capabilities.hpp"
#include "../sequence/push_front.hpp"
#include "../sequence/take.hpp"
#include "../vocabulary.hpp"
namespace boost {
	namespace tmp {
		template <typename F = less_<>, typename C = listify_>
		struct sort_ {};

		namespace detail {
			namespace btree {
				template <typename... Ts>
				struct blist {};
				template <typename L, typename E, typename R>
				struct bnode {};
				template <typename T>
				struct bun;
				template <bool, template <typename...> class F>
				struct bpush;
				template <template <typename...> class F>
				struct bpush<false, F> {
					template <typename T, typename L, typename E, typename R>
					using n = bnode<L, E, typename bun<R>::template f<F, T>>;
					template <typename T, typename LL, typename LE, typename LR, typename E,
					          typename RL, typename RE, typename RR>
					using nn = typename bpush<F<T, RE>::value, F>::template nn_0<T, LL, LE, LR, E,
					                                                             RL, RE, RR>;
					template <typename T, typename LL, typename LE, typename LR, typename E,
					          typename RL, typename RE, typename RR>
					using nn_0 = bnode<bnode<bnode<LL, LE, LR>, E, RL>, RE,
					                   typename bun<RR>::template f<F, T>>;
					template <typename T, typename LL, typename LE, typename LR, typename E,
					          typename RL, typename RE, typename RR>
					using nn_1 = bnode<bnode<LL, LE, typename bun<LR>::template f<F, T>>, E,
					                   bnode<RL, RE, RR>>;
					template <typename T, typename E>
					using l1 = blist<E, T>;
					template <typename T, typename E0, typename E1>
					using l2_0 = typename bpush<F<T, E1>::value, F>::template l2_1<T, E0, E1>;
					template <typename T, typename E0, typename E1>
					using l2_1 = bnode<blist<E0>, E1, blist<T>>;
				};
				template <template <typename...> class F>
				struct bpush<true, F> {
					template <typename T, typename L, typename E, typename R>
					using n = bnode<typename bun<L>::template f<F, T>, E, R>;
					template <typename T, typename LL, typename LE, typename LR, typename E,
					          typename RL, typename RE, typename RR>
					using nn = typename bpush<F<T, LE>::value, F>::template nn_1<T, LL, LE, LR, E,
					                                                             RL, RE, RR>;
					template <typename T, typename LL, typename LE, typename LR, typename E,
					          typename RL, typename RE, typename RR>
					using nn_0 = bnode<bnode<LL, LE, LR>, E,
					                   bnode<typename bun<RL>::template f<F, T>, RE, RR>>;
					template <typename T, typename LL, typename LE, typename LR, typename E,
					          typename RL, typename RE, typename RR>
					using nn_1 = bnode<typename bun<LL>::template f<F, T>, LE,
					                   bnode<LR, E, bnode<RL, RE, RR>>>;
					template <typename T, typename E>
					using l1 = blist<T, E>;
					template <typename T, typename E0, typename E1>
					using l2_0 = bnode<blist<T>, E0, blist<E1>>;
					template <typename T, typename E0, typename E1>
					using l2_1 = bnode<blist<E0>, T, blist<E1>>;
				};

				template <>
				struct bun<blist<>> {
					template <template <typename...> class F, typename T>
					using f = blist<T>;
				};
				template <typename E>
				struct bun<blist<E>> {
					template <template <typename...> class F, typename T>
					using f = typename bpush<F<T, E>::value, F>::template l1<T, E>;
				};
				template <typename E0, typename E1>
				struct bun<blist<E0, E1>> {
					template <template <typename...> class F, typename T>
					using f = typename bpush<F<T, E0>::value, F>::template l2_0<T, E0, E1>;
				};
				template <typename L, typename E, typename R>
				struct bun<bnode<L, E, R>> {
					template <template <typename...> class F, typename T>
					using f = typename bpush<F<T, E>::value, F>::template n<T, L, E, R>;
				};
				template <typename LL, typename LE, typename LR, typename E, typename RL,
				          typename RE, typename RR>
				struct bun<bnode<bnode<LL, LE, LR>, E, bnode<RL, RE, RR>>> {
					template <template <typename...> class F, typename T>
					using f = typename bpush<F<T, E>::value, F>::template nn<T, LL, LE, LR, E, RL,
					                                                         RE, RR>;
				};
				template <typename LLL, typename LLE, typename LLR, typename LE, typename LR,
				          typename E, typename... Ts>
				struct bun<bnode<bnode<bnode<LLL, LLE, LLR>, LE, LR>, E, blist<Ts...>>> {
					template <template <typename...> class F, typename T>
					using f = typename bpush<F<T, LE>::value, F>::template nn<T, LLL, LLE, LLR, LE,
					                                                          LR, E, blist<Ts...>>;
				};

				template <typename... Ts, typename E, typename RL, typename RE, typename RRL,
				          typename RRE, typename RRR>
				struct bun<bnode<blist<Ts...>, E, bnode<RL, RE, bnode<RRL, RRE, RRR>>>> {
					template <template <typename...> class F, typename T>
					using f =
					        typename bpush<F<T, RE>::value, F>::template nn<T, blist<Ts...>, E, RL,
					                                                        RE, RRL, RRE, RRR>;
				};

				template <typename LL, typename LE, typename LR, typename E, typename RL,
				          typename RE, typename RR>
				struct join7;

				template <typename... LL, typename LE, typename... LR, typename E, typename... RL,
				          typename RE, typename... RR>
				struct join7<blist<LL...>, LE, blist<LR...>, E, blist<RL...>, RE, blist<RR...>> {
					using type = blist<LL..., LE, LR..., E, RL..., RE, RR...>;
				};

				template <typename T>
				struct bflat;

				template <typename L, typename E, typename R>
				struct bflat<bnode<L, E, R>> {
					using type = typename bflat<
					        bnode<typename bflat<L>::type, E, typename bflat<R>::type>>::type;
				};
				template <typename LL, typename LE, typename LR, typename E, typename RL,
				          typename RE, typename RR>
				struct bflat<bnode<bnode<LL, LE, LR>, E, bnode<RL, RE, RR>>> {
					using type =
					        typename join7<typename bflat<LL>::type, LE, typename bflat<LR>::type,
					                       E, typename bflat<RL>::type, RE,
					                       typename bflat<RR>::type>::type;
				};

				template <typename... L, typename E, typename... R>
				struct bflat<bnode<blist<L...>, E, blist<R...>>> {
					using type = blist<L..., E, R...>;
				};
				template <typename... T>
				struct bflat<blist<T...>> {
					using type = blist<T...>;
				};

				template <typename T>
				using collapse_t = typename btree::bflat<T>::type;
			} // namespace btree

			template <typename F>
			struct element_pusher {};
			template <typename F>
			struct dispatch<2, element_pusher<F>> {
				template <typename T, typename U>
				using f = typename btree::bun<T>::template f<dispatch<2, F>::template f, U>;
			};
			template <template <typename...> class F>
			struct dispatch<2, element_pusher<lift_<F>>> {
				template <typename T, typename U>
				using f = typename btree::bun<T>::template f<F, U>;
			};

			template <template <typename...> class F>
			struct pusher {
				template <typename T, typename U>
				using f = typename btree::bun<T>::template f<F, U>;
			};

			template <template <typename...> class F, typename C = identity_,
			          typename Initial = btree::blist<>>
			using make_binary_tree =
			        push_front_<Initial, fold_left_<lift_<pusher<F>::template f>, C>>;

			template <typename C>
			using collapse_unpack = lift_<btree::collapse_t, unpack_<C>>;

			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, sort_<lift_<F>, C>>
			    : dispatch<N, make_binary_tree<F, collapse_unpack<C>, btree::blist<>>> {};

			template <unsigned N, typename F, typename C>
			struct dispatch<N, sort_<F, C>>
			    : dispatch<N, make_binary_tree<dispatch<2, F>::template f, collapse_unpack<C>,
			                                   btree::blist<>>> {};

		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif