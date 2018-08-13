#ifndef BOOST_TMP_UNPACK_HPP_INCLUDED
#define BOOST_TMP_UNPACK_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

namespace boost {
	namespace tmp {
		/// \brief turns a list of types into a variadic pack of those types /
		/// example: call<all<>,ture_,false_,true_> is equivalent to
		/// call<unpack<all<>>,list<true_,false_,true_>>
		template <typename C>
		struct unpack_ {};
		namespace detail {
			template <typename C, typename L>
			struct unpack_impl;
			template <typename C, template <typename...> class Seq, typename... Ls>
			struct unpack_impl<C, Seq<Ls...>> {
				using type = typename dispatch<find_dispatch(sizeof...(Ls)), C>::template f<Ls...>;
			};

			template <typename C>
			struct unpack_impl<C, nothing_> { // in case of nothing_ input give a nothing_ output
				using type = nothing_;
			};

			template <typename C>
			struct dispatch<1, unpack_<C>> {
				template <typename L>
				using f = typename detail::unpack_impl<C, L>::type;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif
