#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/partition.hpp"

namespace partition_test {
	template <int I>
	struct x {
		static constexpr int value = I;
	};

	using xs0 = list_<x<1>, x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>;

	template <typename T>
	using more_than_5 = bool_<(T::value > 5)>;

	using result0 = call_<unpack_<partition_<lift_<more_than_5>>>, xs0>;
	int run() {

		return 0;
	}
} // namespace partition_test