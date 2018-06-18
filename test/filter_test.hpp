#include "../include/boost/tmp/algorithm/filter.hpp"
#include "../include/boost/tmp/is.hpp"
#include "../include/boost/tmp/pack.hpp"
#include "../include/boost/tmp/fusion.hpp"

namespace filter_test {
    using namespace boost::tmp;

    int run() {
        list_<int,int> t1 = call_<filter_<is_<int>>,bool,char,int,int,bool>{};
        std::pair<int,int> t2 = pack_(false,'a',1,2,true) >>= filter_<is_<int>>{} | [](auto l, auto r){ return std::make_pair(l,r);};
        int t3 = pack_(false,'a',1,true) >>= filter_<is_<int>>{} | [](auto l){ return l; };

        return 0;
    }
}