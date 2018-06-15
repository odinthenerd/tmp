#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/count_if.hpp"

namespace count_if_test {
	/*	template <typename T>
	    using divide_by_two_celing = int_<((T::value >> 1) + (T::value & 1))>;
	    template <typename T>
	    using multiply_by_2 = uint_<(T::value << 1)>;
	*/
	template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;
	int run() {
		/*using make_filtered_sequence = make_sequence_<identity_, filter_<lift_<is_even>>>;
		using make_stride2_sequence =
		        lift_<divide_by_two_celing, make_sequence_<lift_<multiply_by_2>>>;
*/
		// call_<make_sequence_<make_algo<make_stride2_sequence>>, extent>{} =
		// call_<make_sequence_<make_algo<make_filtered_sequence>>, extent>{};

		// using m = call_<count_if_<lift_<is_even>>,int_<1>>;
		// using g = typename m::g;

		return 0;
	}
}