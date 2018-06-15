#include "test_util.hpp"

namespace reverse_test {
	int run() {
		using rhs = make_sequence_<identity_, reverse_<reverse_<>>>;
		using lhs = make_sequence_<>;
			call_<make_sequence_<make_algo<lhs>>, extent>{} =
			        call_<make_sequence_<make_algo<rhs>>, extent>{};

		list_<uint_<0>>{} =
				call_<make_sequence_<identity_, reverse_<>>, uint_<1>>{};

		list_<uint_<1>, uint_<0>>{} =
				call_<make_sequence_<identity_, reverse_<>>, uint_<2>>{};

		list_<uint_<2>, uint_<1>, uint_<0>>{} =
				call_<make_sequence_<identity_, reverse_<>>, uint_<3>>{};

		list_<uint_<3>, uint_<2>, uint_<1>, uint_<0>>{} =
				call_<make_sequence_<identity_, reverse_<>>, uint_<4>>{};

		list_<uint_<4>, uint_<3>, uint_<2>, uint_<1>, uint_<0>>{} =
				call_<make_sequence_<identity_, reverse_<>>, uint_<5>>{};

		return 0;
	}
}
