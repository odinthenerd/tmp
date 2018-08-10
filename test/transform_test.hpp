#include "test_util.hpp"

namespace transform_test {
	int run() {
		using rhs = make_sequence_<identity_, transform_<listify_>>;
		using lhs = make_sequence_<listify_>;
		call_<make_sequence_<make_algo<lhs>>, extent>{} =
		        call_<make_sequence_<make_algo<rhs>>, extent>{};

		return 0;
	}
} // namespace transform_test
