#ifndef BOOST_TMP_VOCABULARY_HPP_INCLUDED
#define BOOST_TMP_VOCABULARY_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "lift.hpp"
#include "always.hpp"

namespace boost{
    namespace tmp{
        template<typename...Ts>
        struct list_{};

        using listify_ = lift_<list_>;

        template<unsigned long long V>
        struct uint_{
            static constexpr unsigned long long value = V;
        };
        template<long long>
        struct int_{};
        template<bool B>
        struct bool_{
            static constexpr bool value = B;
        };

        using true_ = bool_<true>;
        using false_ = bool_<false>;

        struct nothing_{};
    }
}
#endif
