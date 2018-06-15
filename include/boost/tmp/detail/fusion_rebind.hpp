#ifndef BOOST_TMP_FUSION_REBIND_HPP_INCLUDED
#define BOOST_TMP_FUSION_REBIND_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

namespace boost{
    namespace tmp{
        namespace fusion{
            //to make a metafunction fusion capable this traits must be specialized
            //with the rebound version of the metafunction to be used in fusion context
            template<typename T>
            struct rebind;
        }
    }
}

#endif