#include "transform_test.hpp"
#include "filter_test.hpp"
#include "fold_left_test.hpp"
#include "zip_with_index_test.hpp"

#include "../include/boost/tmp.hpp"

int main(){
    return transform_test::run() || fold_left_test::run()|| zip_with_index_test::run();
}
