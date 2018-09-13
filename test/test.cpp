#include "contains_test.hpp"
#include "count_if_test.hpp"
#include "erase_test.hpp"
#include "filter_test.hpp"
#include "tee_test.hpp"
#include "find_if_test.hpp"
#include "fold_left_test.hpp"
#include "fold_right_test.hpp"
#include "join_test.hpp"
#include "logic_test.hpp"
#include "partition_test.hpp"
#include "product_test.hpp"
#include "reverse_test.hpp"
#include "sort_test.hpp"
#include "take_test.hpp"
#include "transform_test.hpp"
#include "try_test.hpp"
#include "zip_with_index_test.hpp"

int main() {
	return join_test::run() || transform_test::run() || fold_left_test::run() ||
	       zip_with_index_test::run();
}
