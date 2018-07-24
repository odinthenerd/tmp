#include <memory>
#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/find_if.hpp"

namespace find_if_test {
	template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;
	int run() {

		uint_<8>{} = call_<find_if_<lift_<is_even>>, int_<1>, int_<1>, int_<1>, int_<1>, int_<1>,
		                   int_<1>, int_<1>, int_<1>, int_<2>>{};
		nothing_{} = call_<find_if_<lift_<is_even>>, int_<1>>{};

		uint_<400>{} = call_<make_sequence_<identity_, find_if_<is_<uint_<400>>>>, uint_<500>>{};

		(void)(1 == (val_pack_(false, 'a', 1, true) >>= find_if_<is_<int>>{}));

		std::unique_ptr<int> p = pack_(std::unique_ptr<int>{}) >>= find_if_<always_<true_>>{};

		return 0;
	}
}