#ifndef BOOST_TMP_REMOVE_IF_HPP_INCLUDED
#define BOOST_TMP_REMOVE_IF_HPP_INCLUDED

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
#include "../if.hpp"
#include "../always.hpp"

namespace boost {
	namespace tmp {
		template <typename F, typename C = identity_>
		struct remove_if_ {};
		namespace detail {
			template<unsigned N, typename F, typename C>
			struct dispatch<N,remove_if_<F,C>>{
				template <typename... Ts>
				using f = typename dispatch<N, join_<C>>::template f<typename dispatch<1,if_<F,always_<list_<void>>,always_<list_<>>>>::template f<Ts>...>;
			};
		}
	}
}


#endif