#ifndef BOOST_TMP_UNPACK_HPP_INCLUDED
#define BOOST_TMP_UNPACK_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

namespace boost{
    namespace tmp{
		/// \brief turns a list of types into a variadic pack of those types /
		/// example: call<all<>,ture_,false_,true_> is equivalent to
		/// call<unpack<all<>>,list<true_,false_,true_>>
		template <typename C>
		struct unpack_{};
		namespace detail{
			template <unsigned N, typename C, typename L, typename... Ts>
			struct unpack_impl;
			template <unsigned N, typename C, template <typename...> class Seq, typename... Ls, typename... Ts>
			struct unpack_impl<N, C, Seq<Ls...>, Ts...> {
				using type = typename dispatch<find_dispatch((N -1) + sizeof...(Ls)),C>::template f<Ts..., Ls...>;
			};

			template<unsigned N, typename C>
			struct dispatch<N,unpack_<C>>{
				template <typename... Ls>
				using f = typename detail::unpack_impl<N, C, Ls...>::type;
			};
		}
    }
}

#endif

