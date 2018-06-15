#ifndef BOOST_TMP_ZIP_HPP_INCLUDED
#define BOOST_TMP_ZIP_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../call.hpp"
#include "../vocabulary.hpp"
#include<utility>

namespace boost{
    namespace tmp{
    	template<typename I, typename C = identity_>
    	struct at_{};
		template<typename C = identity_>
		using at0_ = at_<uint_<0>,C>;
		template<typename C = identity_>
		using at1_ = at_<uint_<1>,C>;
		template<typename C = identity_>
		using at2_ = at_<uint_<2>,C>;
		template<typename C = identity_>
		using at3_ = at_<uint_<3>,C>;
		template<typename C = identity_>
		using at4_ = at_<uint_<4>,C>;
		template<typename C = identity_>
		using at5_ = at_<uint_<5>,C>;
		template<typename C = identity_>
		using at6_ = at_<uint_<6>,C>;
		template<typename C = identity_>
		using at7_ = at_<uint_<7>,C>;
		template<typename C = identity_>
		using at8_ = at_<uint_<8>,C>;
		template<typename C = identity_>
		using at9_ = at_<uint_<9>,C>;
		namespace detail{
			template<unsigned N, typename I, typename C>
			struct dispatch<N,at_<I,C>>{
				//TODO implement
			};
			template<unsigned N, typename C>
			struct dispatch<N,at_<uint_<0>,C>>{
				template<typename T, typename...Ts>
				using f = typename dispatch<1,C>::template f<T>;
			};
			template<unsigned N, typename C>
			struct dispatch<N,at_<uint_<1>,C>>{
				template<typename T0, typename T1, typename...Ts>
				using f = typename dispatch<1,C>::template f<T1>;
			};
		}
    }
}

#endif

