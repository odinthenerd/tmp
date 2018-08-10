#include "test_util.hpp"

namespace zip_with_index_test {
	template <typename T>
	using doubleify = list_<T, T>;

	int run() {
		using lhs = make_sequence_<lift_<doubleify>>;
		using rhs = make_sequence_<identity_, zip_with_index_<>>;
		call_<make_sequence_<make_algo<lhs>>, extent>{} =
		        call_<make_sequence_<make_algo<rhs>>, extent>{};

		return 0;
	}
} // namespace zip_with_index_test
