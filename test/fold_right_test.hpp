#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/fold_right.hpp"

namespace fold_right_test {
	template <typename T, typename U>
	using add = uint_<(T::value + U::value)>;
	int run() {
		uint_<1>{}  = call_<fold_right_<lift_<add>>, uint_<1>>{};
		uint_<3>{}  = call_<fold_right_<lift_<add>>, uint_<1>, uint_<2>>{};
		uint_<6>{}  = call_<fold_right_<lift_<add>>, uint_<1>, uint_<2>, uint_<3>>{};
		uint_<10>{} = call_<fold_right_<lift_<add>>, uint_<1>, uint_<2>, uint_<3>, uint_<4>>{};
		uint_<20>{} = call_<fold_right_<lift_<add>>, uint_<1>, uint_<1>, uint_<1>, uint_<1>,
		                    uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>,
		                    uint_<2>, uint_<3>, uint_<4>>{};
		return 0;
	}
} // namespace fold_right_test
