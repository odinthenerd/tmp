#include "../include/boost/tmp/sequence/set.hpp"
#include "../include/boost/tmp/sequence/push_front.hpp"

namespace set_test {
    using namespace boost::tmp;
    using test = call_<make_unique,int_<1>,int_<2>,int_<1>,int_<2>>;
    int run() {

    }
}