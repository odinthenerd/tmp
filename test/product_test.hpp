#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/product.hpp"

namespace product_test {
	template <int I>
	struct x {
		static constexpr int value = I;
	};

	using xl0 = list_<x<1>, x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>;
	using xr0 = list_<x<1>, x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>;

	using result0 = call_<product_<>, xl0, xr0>;
	int run() {

		return 0;
	}
} // namespace product_test