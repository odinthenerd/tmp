#include "test_util.hpp"
#include "../include/boost/tmp/sequence/join.hpp"

namespace join_test {
	int run() {
		using make_listified_sequence = make_sequence_<listify_, push_front_<list_<>, join_<>>>;
		call_<make_sequence_<make_algo<make_sequence_<>>>, extent>{} =
		        call_<make_sequence_<make_algo<make_listified_sequence>>, extent>{};

		return 0;
	}
} // namespace join_test