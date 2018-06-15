#include "../include/boost/tmp/algorithm/transform.hpp"

namespace transform_test {
    using namespace boost::tmp;

    template<typename T>
    using intify = int;

    int run() {
        list_<int,int> lhs = call_<transform_<lift_<intify>>,bool,char>{};

//        transform<>{} << [](){};

        return 0;
    }
}
