#include <memory>
#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/find_if.hpp"
#include "../include/boost/tmp/is.hpp"
#include "../include/boost/tmp/pack.hpp"
#include "../include/boost/tmp/sequence/unpack.hpp"

namespace find_if_test {
	template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

	namespace tmp = boost::tmp;

	constexpr auto a = tmp::val_pack_(

	);

	template <int X>
	struct equals_to {
		template <typename Y>
		using f = tmp::bool_<(Y::value == X)>;
	};

	int run() {

		uint_<8>{} = call_<find_if_<lift_<is_even>>, int_<1>, int_<1>, int_<1>, int_<1>, int_<1>,
		                   int_<1>, int_<1>, int_<1>, int_<2>>{};
		nothing_{} = call_<find_if_<lift_<is_even>>, int_<1>>{};

		uint_<400>{} = call_<make_sequence_<identity_, find_if_<is_<uint_<400>>>>, uint_<500>>{};
#ifdef BOOST_TMP_CPP14

		constexpr auto xs0 = tmp::val_pack_(

		);
		constexpr auto result0 = xs0 >>= tmp::find_if_<tmp::lift_<equals_to<0>::template f>>{};

		constexpr auto xs1 = tmp::val_pack_(
		        tmp::int_<1>{}, tmp::int_<2>{}, tmp::int_<3>{}, tmp::int_<4>{}, tmp::int_<5>{},
		        tmp::int_<6>{}, tmp::int_<7>{}, tmp::int_<8>{}, tmp::int_<9>{}, tmp::int_<10>{});

		constexpr auto result1 = xs1 >>= tmp::find_if_<tmp::lift_<equals_to<10>::template f>>{};

		(void)(1 == (val_pack_(false, 'a', 1, true) >>= find_if_<is_<int>>{}));

		std::unique_ptr<int> p = pack_(std::unique_ptr<int>{}) >>= find_if_<always_<true_>>{};
#endif
		return 0;
	}
} // namespace find_if_test