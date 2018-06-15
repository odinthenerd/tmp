#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/filter.hpp"
#include "../include/boost/tmp/fusion.hpp"
#include "../include/boost/tmp/is.hpp"
#include "../include/boost/tmp/pack.hpp"
#include "../include/boost/tmp/sequence/zip.hpp"

namespace filter_test {
	template <typename T>
	using divide_by_two_celing = int_<((T::value >> 1) + (T::value & 1))>;
	template <typename T>
	using multiply_by_2 = uint_<(T::value << 1)>;

	template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;
	int run() {
		using make_filtered_sequence = make_sequence_<identity_, filter_<lift_<is_even>>>;
		using make_stride2_sequence =
		        lift_<divide_by_two_celing, make_sequence_<lift_<multiply_by_2>>>;

		call_<make_sequence_<make_algo<make_stride2_sequence>>, extent>{} =
		 call_<make_sequence_<make_algo<make_filtered_sequence>>, extent>{};

		// fusion
		int i = 1;
		std::pair<int, int>{} = pack_(false, 'a', i, 2, true) >>=
		        filter_<lift_<std::remove_reference_t, is_<int>>>{} |
		        [](auto l, auto r) { return std::make_pair(l, r); };
		(void)(1 ==
		       (pack_(false, 'a', 1, true) >>=
		        filter_<lift_<std::remove_reference_t, is_<int>>>{} | [](auto l) { return l; }));
		pack_() = pack_() >>= filter_<lift_<is_even>>{};

		return 0;
	}
}