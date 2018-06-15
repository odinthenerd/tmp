#include "../include/boost/tmp/algorithm/fold_left.hpp"

namespace fold_left_test {
	template <typename T, typename U>
	using intify = int;

	unsigned sigma(unsigned running, unsigned count_down) {
		return count_down == 0 ? running : sigma(running + count_down, count_down - 1);
	}

	int run() {
		int lhs = call_<fold_left_<lift_<intify>>, bool, char>{};
		(void)lhs;
		return 0;
	}
}
