#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/contains.hpp"
#include "../include/boost/tmp/is.hpp"
namespace contains_test {
	template <int>
	struct x;

	using xs0 = list_<x<1>, x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>;

	using result0 = call_<unpack_<contains_<is_<x<0>>>>, xs0>;
	using result1 = call_<unpack_<contains_<is_<x<1>>>>, xs0>;
	using result2 = call_<unpack_<contains_<is_<x<5>>>>, xs0>;
	using result3 = call_<unpack_<contains_<is_<x<10>>>>, xs0>;

	int run() {

		return 0;
	}
} // namespace contains_test