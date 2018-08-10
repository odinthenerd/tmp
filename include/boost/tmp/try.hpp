#ifndef BOOST_TMP_TRY_HPP_INCLUDED
#define BOOST_TMP_TRY_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "always.hpp"
#include "detail/dispatch.hpp"
#include "identity.hpp"
#include "sequence/unpack.hpp"
#include "vocabulary.hpp"

namespace boost {
	namespace tmp {

		template <template <typename...> class F, typename C = identity_>
		struct try_ {};

		namespace detail {
			template <typename T>
			struct t_ {
				using type = T;
			};
			template <template <typename...> class F, typename... Ts>
			t_<F<Ts...>> try_f(lift_<F>, list_<Ts...>);
			t_<nothing_> try_f(...);

			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, try_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<typename decltype(
				        try_f(lift_<F>{}, list_<Ts...>{}))::type>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost
#endif
