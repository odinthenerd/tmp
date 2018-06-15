#ifndef BOOST_TMP_FILTER_HPP_INCLUDED
#define BOOST_TMP_FILTER_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../call.hpp"
#include "../vocabulary.hpp"
#include "../detail/dispatch.hpp"
#include "../sequence/join.hpp"
#include "../sequence/unpack.hpp"
#include "../sequence/at.hpp"
#include "../if.hpp"

namespace boost {
	namespace tmp {
		template <typename F, typename C = listify_>
		struct filter_{};

		namespace fusion{
                template<typename F, typename C>
                struct rebind<filter_<F, C>> {
                    using type = filter_<unpack_<at0_<F>>, typename rebind<C>::type>;
                };
		}

		namespace detail {
			template<unsigned N, typename F, typename C>
			struct dispatch<N,filter_<F,C>>{
				template <typename... Ts>
				using f = typename dispatch<(N + (N>sizeof...(Ts))), join_<C>>::template f<typename dispatch<1,if_<F,listify_,always_<list_<>>>>::template f<Ts>...>;
			};
		}
	}
}


#endif