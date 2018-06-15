#ifndef BOOST_TMP_DISPATCH_HPP_INCLUDED
#define BOOST_TMP_DISPATCH_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

namespace boost{
    namespace tmp {
        namespace detail {
            // specialize for 12
            constexpr unsigned find_dispatch(unsigned n){
                    return n <= 4 ? n : n < 8 ? 5 :
                                        n == 8? 8 :
                                        n < 16 ? 9 :
                                        n == 16 ? 16 :
                                        n < 32 ? 17 :
                                        n == 32 ? 32 :
                                        n < 64 ? 33 :
                                        n == 64 ? 64 :
                                        n < 128 ? 65 :
                                        n == 128 ? 128 :
                                        n < 256 ? 129 :
                                        n == 256 ? 256 :
                                        n < 512 ? 257 :
                                        n == 512 ? 512 :
                                        n < 1024 ? 513 :
                                        n == 1024 ? 1024 :
                                        n < 2048 ? 1025 :
                                        n == 2048 ? 2048 :
                                        n < 4096 ? 2049 :
                                        n == 4096 ? 4096 :
                                        n < 8192 ? 4097 :
                                        n == 8192 ? 8192 :
                                        8193;
            }

            template<unsigned N, typename T>
            struct dispatch;
        }
    }
}
#endif
