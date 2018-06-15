#ifndef BOOST_TMP_FUSION_HPP_INCLUDED
#define BOOST_TMP_FUSION_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
#include "detail/fusion_execute.hpp"
#include "detail/fusion_rebind.hpp"
#include "pack.hpp"
#include "sequence/fork.hpp"
namespace boost {
	namespace tmp {
		namespace fusion {
			template <typename... Ps, typename T, typename C>
			constexpr auto operator>>=(fast_pack<Ps...> p, expr<T, C> &&ex) {
				auto tree  = ex.reverse();
				using type = typename decltype(tree)::template exec<typename Ps::type...>;
				return tree.f(type{}, static_cast<typename Ps::type>(static_cast<Ps &>(p).data)...);
			};
			// will SFINAE if there is no rebind specialization
			template <typename... Ps, typename F, typename RF = typename rebind<F>::type>
			constexpr auto operator>>=(fast_pack<Ps...> p, F f) {
				using type = typename RF::template exec<typename Ps::type...>;
				return RF{}.f(type{}, static_cast<typename Ps::type>(static_cast<Ps &>(p).data)...);
			};
			// will SFINAE if rhs can not be called with pack parameters
			template <typename... Ps, typename F>
			constexpr auto operator>>=(fast_pack<Ps...> p, F f)
			        -> decltype(f(static_cast<Ps &>(p).data...)) {
				return f(static_cast<Ps &>(p).data...);
			};
		}
	}
}

#endif