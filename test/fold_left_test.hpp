#include "../include/boost/tmp/algorithm/fold_left.hpp"

namespace fold_left_test {
    using namespace boost::tmp;

    template<typename T, typename U>
    using intify = int;

    int run() {
        int lhs = call_<fold_left_<lift_<intify>>,bool,char>{};

        return 0;
    }
}
