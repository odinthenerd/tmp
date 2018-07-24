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

	namespace tmp = boost::tmp;
	template <typename N>
	using is_even = tmp::bool_<N::value % 2 == 0>;
	using xs0     = tmp::list_<tmp::int_<1>, tmp::int_<2>, tmp::int_<3>, tmp::int_<4>, tmp::int_<5>,
	                       tmp::int_<6>, tmp::int_<7>, tmp::int_<8>, tmp::int_<9>, tmp::int_<10>>;
	using result0 = tmp::call_<tmp::unpack_<tmp::filter_<tmp::lift_<is_even>>>, xs0>;

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