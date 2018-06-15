#include "../include/boost/tmp/sequence/zip_with_index.hpp"

namespace zip_with_index_test {
    using namespace boost::tmp;

    template<typename T>
    using intify = int;

    int run() {
        list_<list_<uint_<0>,bool>,list_<uint_<1>,char>> lhs = call_<zip_with_index_<listify_>,bool,char>{};

        return 0;
    }
}
