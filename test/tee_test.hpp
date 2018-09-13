#include "test_util.hpp"
#include "../include/boost/tmp/sequence/tee.hpp"

namespace tee_test {
	using namespace boost::tmp;

	int run() {
		{
			list_<list_<>>{}          = call_<tee_<listify_, listify_>>{};
			list_<list_<int>>{}       = call_<tee_<listify_, listify_>, int>{};
			list_<list_<int, bool>>{} = call_<tee_<listify_, listify_>, int, bool>{};
			list_<list_<int, bool>, int, bool>{} =
			        call_<tee_<listify_, forward_as_pack_, listify_>, int, bool>{};
			list_<list_<int, bool>, list_<int, bool>>{} =
			        call_<tee_<listify_, listify_, listify_>, int, bool>{};
			list_<list_<int, bool>, list_<int, bool>, int, bool>{} =
			        call_<tee_<listify_, listify_, forward_as_pack_, listify_>, int, bool>{};
			list_<list_<int, bool>, list_<int, bool>, list_<int, bool>>{} =
			        call_<tee_<listify_, listify_, listify_, listify_>, int, bool>{};
			list_<list_<int, bool>, list_<int, bool>, list_<int, bool>, int, bool>{} =
			        call_<tee_<listify_, listify_, listify_, forward_as_pack_, listify_>, int,
			              bool>{};
			list_<list_<int, bool>, list_<int, bool>, list_<int, bool>, list_<int, bool>>{} =
			        call_<tee_<listify_, listify_, listify_, listify_, listify_>, int, bool>{};
			list_<list_<int, bool>, list_<int, bool>, list_<int, bool>, list_<int, bool>, int,
			      bool>{} =
			        call_<tee_<listify_, listify_, listify_, listify_, forward_as_pack_, listify_>,
			              int, bool>{};
		}
		{
			true_{}  = call_<tee_<is_<int>, and_<>>, int>{};
			false_{} = call_<tee_<is_<int>, is_<int>, and_<>>, char>{};
			false_{} = call_<tee_<is_<int>, is_<int>, is_<int>, and_<>>, char>{};
			false_{} = call_<tee_<is_<int>, identity_, and_<>>,
			                 char>{}; // short circuiting should save from hard error
			false_{} = call_<tee_<is_<int>, identity_, is_<int>, and_<>>,
			                 char>{}; // short circuiting should save from hard error
		}
		{
			true_{}  = call_<tee_<is_<int>, or_<>>, int>{};
			false_{} = call_<tee_<is_<int>, is_<int>, or_<>>, char>{};
			false_{} = call_<tee_<is_<int>, is_<int>, is_<int>, or_<>>, char>{};
			true_{}  = call_<tee_<is_<int>, identity_, or_<>>,
                            int>{}; // short circuiting should save from hard error
			true_{}  = call_<tee_<is_<int>, identity_, is_<int>, or_<>>,
                            int>{}; // short circuiting should save from hard error
		}

		return 0;
	}
} // namespace tee_test