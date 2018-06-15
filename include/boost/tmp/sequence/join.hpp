#ifndef BOOST_TMP_JOIN_HPP_INCLUDED
#define BOOST_TMP_JOIN_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

namespace boost{
    namespace tmp{
		template <typename C>
		struct join_ {};
		namespace detail{
			template<typename C>
			struct dispatch<1,join_<C>>{
				template<typename>
				struct impl;
				template<template<typename...> class L, typename...Ts>
				struct impl<L<Ts...>>{
					using type = call_<C,Ts...>;
				};
				template <typename T>
				using f = typename impl<T>::type;
			};
			template<typename C>
			struct dispatch<2,join_<C>>{
				template<typename,typename>
				struct impl;
				template<template<typename...> class L0,template<typename...> class L1, typename...T0s, typename...T1s>
				struct impl<L0<T0s...>,L1<T1s...>>{
					using type = call_<C,T0s...,T1s...>;
				};
				template <typename T0, typename T1>
				using f = typename impl<T0, T1>::type;
			};
			template<typename C>
			struct dispatch<3,join_<C>>{
				template<typename,typename,typename>
				struct impl;
				template<template<typename...> class L0,
						template<typename...> class L1,
						template<typename...> class L2, typename...T0s, typename...T1s, typename...T2s>
				struct impl<L0<T0s...>,L1<T1s...>,L2<T2s...>>{
					using type = call_<C,T0s...,T1s...,T2s...>;
				};
				template <typename T0, typename T1, typename T2>
				using f = typename impl<T0, T1, T2>::type;
			};
            template<typename C>
            struct dispatch<4,join_<C>>{
                template<typename,typename,typename,typename>
                struct impl;
                template<template<typename...> class L0,
                        template<typename...> class L1,
                        template<typename...> class L2,
                        template<typename...> class L3, typename...T0s, typename...T1s, typename...T2s, typename...T3s>
                struct impl<L0<T0s...>,L1<T1s...>,L2<T2s...>,L3<T3s...>>{
                    using type = call_<C,T0s...,T1s...,T2s...,T3s...>;
                };
                template <typename T0, typename T1, typename T2, typename T3>
                using f = typename impl<T0, T1, T2, T3>::type;
            };
            template<typename C>
            struct dispatch<5,join_<C>>{
                template<typename,typename,typename,typename,typename,typename,typename,typename>
                struct impl;
                template<template<typename...> class L0,
                        template<typename...> class L1,
                        template<typename...> class L2,
                        template<typename...> class L3,
                        template<typename...> class L4,
                        template<typename...> class L5,
                        template<typename...> class L6,
                        template<typename...> class L7, typename...T0s, typename...T1s, typename...T2s, typename...T3s,
                        typename...T4s, typename...T5s, typename...T6s, typename...T7s>
                struct impl<L0<T0s...>,L1<T1s...>,L2<T2s...>,L3<T3s...>,L4<T4s...>,L5<T5s...>,L6<T6s...>,L7<T7s...>>{
                    using type = call_<C,T0s...,T1s...,T2s...,T3s...>;
                };
                template <typename T0, typename T1, typename T2, typename T3,typename T4=list_<>, typename T5=list_<>, typename T6=list_<>, typename T7=list_<>>
                using f = typename impl<T0, T1, T2, T3, T4, T5, T6, T7>::type;
            };
			template<typename C>
			struct dispatch<8,join_<C>>:dispatch<5,join_<C>>{};
		}
    }
}

#endif

