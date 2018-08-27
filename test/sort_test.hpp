#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/sort.hpp"
namespace sort_test {
	template <typename T, typename U>
	using less = bool_<(T::value < U::value)>;

	template <typename T, typename U>
	using push_ = typename T::template push<U, less>;
	int run() {
		list_<uint_<0>, uint_<1>, uint_<2>> r0 =
		        call_<sort_<lift_<less>>, uint_<1>, uint_<0>, uint_<2>>{};
		using m  = call_<sort_<lift_<less>>, uint_<0>, uint_<27>, uint_<87>, uint_<3>, uint_<56>,
                        uint_<76>, uint_<94>, uint_<17>, uint_<74>, uint_<55>, uint_<96>, uint_<54>,
                        uint_<93>, uint_<79>, uint_<14>, uint_<8>, uint_<31>, uint_<23>, uint_<25>,
                        uint_<34>, uint_<9>, uint_<44>, uint_<63>, uint_<4>, uint_<72>, uint_<46>,
                        uint_<49>, uint_<7>, uint_<83>, uint_<77>, uint_<61>, uint_<81>, uint_<91>,
                        uint_<69>, uint_<52>, uint_<28>, uint_<19>, uint_<57>, uint_<64>, uint_<75>,
                        uint_<2>, uint_<62>, uint_<43>, uint_<42>, uint_<5>, uint_<16>, uint_<18>,
                        uint_<41>, uint_<39>, uint_<6>, uint_<92>, uint_<60>, uint_<1>, uint_<35>,
                        uint_<29>, uint_<51>, uint_<12>, uint_<36>, uint_<24>, uint_<53>, uint_<11>,
                        uint_<32>, uint_<67>, uint_<58>, uint_<80>, uint_<86>, uint_<33>, uint_<85>,
                        uint_<15>, uint_<90>, uint_<20>, uint_<30>, uint_<50>, uint_<98>, uint_<99>,
                        uint_<70>, uint_<21>, uint_<95>, uint_<73>, uint_<78>, uint_<26>, uint_<38>,
                        uint_<82>, uint_<47>, uint_<40>, uint_<66>, uint_<59>, uint_<13>, uint_<89>,
                        uint_<71>, uint_<88>, uint_<37>, uint_<22>, uint_<84>, uint_<10>, uint_<97>,
                        uint_<68>, uint_<65>, uint_<48>, uint_<45>>;
		using j  = call_<make_sequence_<>, uint_<100>>;
		j r1     = m{};
		using mm = call_<sort_<lift_<less>>, int_<19>, int_<2>, int_<20>, int_<9>, int_<11>,
		                 int_<18>, int_<7>, int_<14>, int_<5>, int_<3>, int_<6>, int_<15>, int_<10>,
		                 int_<8>, int_<17>, int_<12>, int_<4>, int_<1>, int_<16>, int_<13>>;

		return 0;
	}
} // namespace sort_test
/*
 *
 * typename dispatch<find_dispatch(sizeof...(Ts)),
                            drop_<uuint_<64>,make_binary_tree<
                                F,
                                lift_<tree::balance_tree64>,
                                typename
dispatch<find_dispatch(sizeof...(Ts)),take_<uuint_<64>,make_binary_tree<F>>>::template f<Ts...>
                        >>>::template f<Ts...>

boost::detail::tree::node<
    boost::detail::tree::node<
        boost::detail::tree::left_node<
            boost::detail::tree::leaf_node<
                boost::uint_<1>
            >,
            boost::uint_<2>
        >,
        boost::uint_<3>,
        boost::detail::tree::node<
            boost::detail::tree::node<
                boost::detail::tree::node<
                    boost::detail::tree::right_node<
                        boost::uint_<4>,
                        boost::detail::tree::left_node<
                             boost::detail::tree::right_node<
                                 boost::uint_<5>,
                                     boost::detail::tree::leaf_node<boost::uint_<6> >
                                 >,
                                 boost::uint_<7>
                             >
                         >,
                         boost::uint_<8>,
                         boost::detail::tree::right_node<
                             boost::uint_<9>,
                             boost::detail::tree::node<
                                 boost::detail::tree::left_node<
                                     boost::detail::tree::leaf_node<boost::uint_<10> >,
                                     boost::uint_<11>
                                 >,
                             boost::uint_<12>,
                         boost::detail::tree::leaf_node<boost::uint_<13> >
                     >
                 >
             >,
             'Äboost::uint_<14>,
boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::uint_<15> >, boost::uint_<16> >
>, boost::uint_<17>,
boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::leaf_node<boost::uint_<18>
>, boost::uint_<19>, boost::detail::tree::right_node<boost::uint_<20>,
boost::detail::tree::right_node<boost::uint_<21>, boost::detail::tree::leaf_node<boost::uint_<22> >
> > >, boost::uint_<23>, boost::detail::tree::node<boost::detail::tree::leaf_node<boost::uint_<24>
>, boost::uint_<25>, boost::detail::tree::leaf_node<boost::uint_<26> > > > > >, boost::uint_<27>,
boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::left_node<boost::detail::tree::node<boost::detail::tree::right_node<boost::uint_<28>,
boost::detail::tree::right_node<boost::uint_<29>, boost::detail::tree::leaf_node<boost::uint_<30> >
> >, boost::uint_<31>, boost::detail::tree::node<boost::detail::tree::right_node<boost::uint_<32>,
boost::detail::tree::leaf_node<boost::uint_<33> > >, boost::uint_<34>,
boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::left_node<boost::detail::tree::left_node<boost::detail::tree::node<boost::detail::tree::right_node<boost::uint_<35>,
boost::detail::tree::right_node<boost::uint_<36>,
boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::uint_<37> >, boost::uint_<38> >
> >, boost::uint_<39>, boost::detail::tree::leaf_node<boost::uint_<40> > >, boost::uint_<41> >,
boost::uint_<42> >, boost::uint_<43> >, boost::uint_<44>,
boost::detail::tree::node<boost::detail::tree::leaf_node<boost::uint_<45> >, boost::uint_<46>,
boost::detail::tree::node<boost::detail::tree::right_node<boost::uint_<47>,
boost::detail::tree::leaf_node<boost::uint_<48> > >, boost::uint_<49>,
boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::uint_<50>
>, boost::uint_<51> >, boost::uint_<52>, boost::detail::tree::leaf_node<boost::uint_<53> > > > > > >
>, boost::uint_<54> >, boost::uint_<55> >, boost::uint_<56>,
boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::right_node<boost::uint_<57>,
boost::detail::tree::left_node<boost::detail::tree::right_node<boost::uint_<58>,
boost::detail::tree::leaf_node<boost::uint_<59> > >, boost::uint_<60> > >, boost::uint_<61>,
boost::detail::tree::leaf_node<boost::uint_<62> > >, boost::uint_<63>,
boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::right_node<boost::uint_<64>,
boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::uint_<65>
>, boost::uint_<66> >, boost::uint_<67>, boost::detail::tree::leaf_node<boost::uint_<68> > > >,
boost::uint_<69>, boost::detail::tree::right_node<boost::uint_<70>,
boost::detail::tree::leaf_node<boost::uint_<71> > > >, boost::uint_<72>,
boost::detail::tree::leaf_node<boost::uint_<73> > > >, boost::uint_<74>,
boost::detail::tree::leaf_node<boost::uint_<75> > >, boost::uint_<76>,
boost::detail::tree::node<boost::detail::tree::right_node<boost::uint_<77>,
boost::detail::tree::leaf_node<boost::uint_<78> > >, boost::uint_<79>,
boost::detail::tree::node<boost::detail::tree::node<boost::detail::tree::leaf_node<boost::uint_<80>
>, boost::uint_<81>, boost::detail::tree::leaf_node<boost::uint_<82> > >, boost::uint_<83>,
boost::detail::tree::left_node<boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::uint_<84>
>, boost::uint_<85> >, boost::uint_<86> > > > > >, boost::uint_<87>,
boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::node<boost::detail::tree::left_node<boost::detail::tree::left_node<boost::detail::tree::leaf_node<boost::uint_<88>
>, boost::uint_<89> >, boost::uint_<90> >, boost::uint_<91>,
boost::detail::tree::leaf_node<boost::uint_<92> > >, boost::uint_<93> >, boost::uint_<94>,
boost::detail::tree::node<boost::detail::tree::leaf_node<boost::uint_<95> >, boost::uint_<96>,
boost::detail::tree::left_node<boost::detail::tree::node<boost::detail::tree::leaf_node<boost::uint_<97>
>, boost::uint_<98>, boost::detail::tree::leaf_node<boost::uint_<99> > >, boost::uint_<100> > > > >
>'} to non-scalar type 'boost::call_<boost::make_sequence_<>, boost::uuint_<100> >' {aka
'boost::list_<boost::uuint_<0>, boost::uuint_<1>, boost::uuint_<2>, boost::uuint_<3>,
boost::uuint_<4>, boost::uuint_<5>, boost::uuint_<6>, boost::uuint_<7>, boost::uuint_<8>,
boost::uuint_<9>, boost::uuint_<10>, boost::uuint_<11>, boost::uuint_<12>, boost::uuint_<13>,
boost::uuint_<14>, boost::uuint_<15>, boost::uuint_<16>, boost::uuint_<17>, boost::uuint_<18>,
boost::uuint_<19>, boost::uuint_<20>, boost::uuint_<21>, boost::uuint_<22>, boost::uuint_<23>,
boost::uuint_<24>, boost::uuint_<25>, boost::uuint_<26>, boost::uuint_<27>, boost::uuint_<28>,
boost::uuint_<29>, boost::uuint_<30>, boost::uuint_<31>, boost::uuint_<32>, boost::uuint_<33>,
boost::uuint_<34>, boost::uuint_<35>, boost::uuint_<36>, boost::uuint_<37>, boost::uuint_<38>,
boost::uuint_<39>, boost::uuint_<40>, boost::uuint_<41>, boost::uuint_<42>, boost::uuint_<43>,
boost::uuint_<44>, boost::uuint_<45>, boost::uuint_<46>, boost::uuint_<47>, boost::uuint_<48>,
boost::uuint_<49>, boost::uuint_<50>, boost::uuint_<51>, boost::uuint_<52>, boost::uuint_<53>,
boost::uuint_<54>, boost::uuint_<55>, boost::uuint_<56>, boost::uuint_<57>, boost::uuint_<58>,
boost::uuint_<59>, boost::uuint_<60>, boost::uuint_<61>, boost::uuint_<62>, boost::uuint_<63>,
boost::uuint_<64>, boost::uuint_<65>, boost::uuint_<66>, boost::uuint_<67>, boost::uuint_<68>,
boost::uuint_<69>, boost::uuint_<70>, boost::uuint_<71>, boost::uuint_<72>, boost::uuint_<73>,
boost::uuint_<74>, boost::uuint_<75>, boost::uuint_<76>, boost::uuint_<77>, boost::uuint_<78>,
boost::uuint_<79>, boost::uuint_<80>, boost::uuint_<81>, boost::uuint_<82>, boost::uuint_<83>,
boost::uuint_<84>, boost::uuint_<85>, boost::uuint_<86>, boost::uuint_<87>, boost::uuint_<88>,
boost::uuint_<89>, boost::uuint_<90>, boost::uuint_<91>, boost::uuint_<92>, boost::uuint_<93>,
boost::uuint_<94>, boost::uuint_<95>, boost::uuint_<96>, boost::uuint_<97>, boost::uuint_<98>,
boost::uuint_<99> >'} requested
             _
             _

   call_<make_sequence_<>,uuint_<100>> r1 = call_<detail::make_binary_tree<lift_<less>>,uint_<27>,
uint_<87>, uint_<3>, uint_<56>, uint_<76>, uint_<94>, uint_<17>, uint_<74>, uint_<55>, uint_<96>,
uint_<54>, uint_<93>, uint_<79>, uint_<14>, uint_<8>, uint_<31>, uint_<23>, uint_<25>, uint_<34>,
uint_<9>, uint_<44>, uint_<63>, uint_<4>, uint_<72>, uint_<46>, uint_<49>, uint_<7>, uint_<100>,
uint_<83>, uint_<77>, uint_<61>, uint_<81>, uint_<91>, uint_<69>, uint_<52>, uint_<28>, uint_<19>,
uint_<57>, uint_<64>, uint_<75>, uint_<2>, uint_<62>, uint_<43>, uint_<42>, uint_<5>, uint_<16>,
uint_<18>, uint_<41>, uint_<39>, uint_<6>, uint_<92>, uint_<60>, uint_<1>, uint_<35>, uint_<29>,
uint_<51>, uint_<12>, uint_<36>, uint_<24>, uint_<53>, uint_<11>, uint_<32>, uint_<67>, uint_<58>,
uint_<80>, uint_<86>, uint_<33>, uint_<85>, uint_<15>, uint_<90>, uint_<20>, uint_<30>, uint_<50>,
uint_<98>, uint_<99>, uint_<70>, uint_<21>, uint_<95>, uint_<73>, uint_<78>, uint_<26>, uint_<38>,
uint_<82>, uint_<47>, uint_<40>, uint_<66>, uint_<59>, uint_<13>, uint_<89>, uint_<71>, uint_<88>,
uint_<37>, uint_<22>, uint_<84>, uint_<10>, uint_<97>, uint_<68>, uint_<65>, uint_<48>,
uint_<45>>{};


boost::list_<
        boost::uint_<1>, boost::uint_<1>, boost::uint_<2>, boost::uint_<2>, boost::uint_<3>,
boost::uint_<4>, boost::uint_<5>, boost::uint_<5>, boost::uint_<6>, boost::uint_<6>, boost::uint_<7>,
boost::uint_<8>, boost::uint_<9>, boost::uint_<10>, boost::uint_<10>, boost::uint_<11>,
boost::uint_<11>, boost::uint_<12>, boost::uint_<12>, boost::uint_<13>, boost::uint_<13>,
boost::uint_<14>, boost::uint_<15>, boost::uint_<16>, boost::uint_<16>, boost::uint_<17>,
boost::uint_<18>, boost::uint_<18>, boost::uint_<19>, boost::uint_<20>, boost::uint_<21>,
boost::uint_<22>, boost::uint_<22>, boost::uint_<23>, boost::uint_<24>, boost::uint_<24>,
boost::uint_<25>, boost::uint_<26>, boost::uint_<27>, boost::uint_<28>, boost::uint_<29>,
boost::uint_<29>, boost::uint_<30>, boost::uint_<31>, boost::uint_<32>, boost::uint_<32>,
boost::uint_<33>, boost::uint_<34>, boost::uint_<35>, boost::uint_<35>, boost::uint_<36>,
boost::uint_<36>, boost::uint_<37>, boost::uint_<37>, boost::uint_<38>, boost::uint_<39>,
boost::uint_<39>, boost::uint_<40>, boost::uint_<40>, boost::uint_<41>, boost::uint_<41>,
boost::uint_<42>, boost::uint_<42>, boost::uint_<43>, boost::uint_<43>, boost::uint_<44>,
boost::uint_<45>, boost::uint_<45>, boost::uint_<46>, boost::uint_<47>, boost::uint_<48>,
boost::uint_<48>, boost::uint_<49>, boost::uint_<50>, boost::uint_<51>, boost::uint_<51>,
boost::uint_<52>, boost::uint_<53>, boost::uint_<53>, boost::uint_<54>, boost::uint_<55>,
boost::uint_<56>, boost::uint_<57>, boost::uint_<58>, boost::uint_<58>, boost::uint_<59>,
boost::uint_<59>, boost::uint_<60>, boost::uint_<60>, boost::uint_<61>, boost::uint_<62>,
boost::uint_<62>, boost::uint_<63>, boost::uint_<64>, boost::uint_<65>, boost::uint_<65>,
boost::uint_<66>, boost::uint_<66>, boost::uint_<67>, boost::uint_<67>, boost::uint_<68>,
boost::uint_<68>, boost::uint_<69>, boost::uint_<70>, boost::uint_<71>, boost::uint_<71>,
boost::uint_<72>, boost::uint_<73>, boost::uint_<74>, boost::uint_<75>, boost::uint_<76>,
boost::uint_<77>, boost::uint_<78>, boost::uint_<79>, boost::uint_<80>, boost::uint_<81>,
boost::uint_<82>, boost::uint_<83>, boost::uint_<84>, boost::uint_<84>, boost::uint_<85>,
boost::uint_<86>, boost::uint_<87>, boost::uint_<88>, boost::uint_<88>, boost::uint_<89>,
boost::uint_<89>, boost::uint_<90>, boost::uint_<91>, boost::uint_<92>, boost::uint_<92>,
boost::uint_<93>, boost::uint_<94>, boost::uint_<95>, boost::uint_<96>, boost::uint_<97>,
boost::uint_<97>, boost::uint_<98>, boost::uint_<99>, boost::uint_<100> > >'


::tree::balance_tree64_impl<boost::list_<
        boost::uint_<1>, boost::uint_<2>, boost::uint_<3>, boost::uint_<4>, boost::uint_<5>,
boost::uint_<6>, boost::uint_<7>, boost::uint_<8>, boost::uint_<9>, boost::uint_<10>,
        boost::uint_<11>, boost::uint_<12>, boost::uint_<13>, boost::uint_<14>, boost::uint_<15>,
boost::uint_<16>, boost::uint_<17>, boost::uint_<18>, boost::uint_<19>, boost::uint_<20>,
        boost::uint_<21>, boost::uint_<22>, boost::uint_<23>, boost::uint_<24>, boost::uint_<25>,
boost::uint_<26>, boost::uint_<27>, boost::uint_<28>, boost::uint_<29>, boost::uint_<30>,
        boost::uint_<31>, boost::uint_<32>, boost::uint_<33>, boost::uint_<34>, boost::uint_<35>,
boost::uint_<36>, boost::uint_<37>, boost::uint_<38>, boost::uint_<39>, boost::uint_<40>,
        boost::uint_<41>, boost::uint_<42>, boost::uint_<43>, boost::uint_<44>, boost::uint_<45>,
boost::uint_<46>, boost::uint_<47>, boost::uint_<48>, boost::uint_<49>, boost::uint_<50>,
        boost::uint_<51>, boost::uint_<52>, boost::uint_<53>, boost::uint_<54>, boost::uint_<55>,
boost::uint_<56>, boost::uint_<57>, boost::uint_<58>, boost::uint_<59>, boost::uint_<60>,
        boost::uint_<61>, boost::uint_<62>, boost::uint_<63>, boost::uint_<64>, boost::uint_<65>,
boost::uint_<66>, boost::uint_<67>, boost::uint_<68>, boost::uint_<69>, boost::uint_<70>,
        boost::uint_<71>, boost::uint_<72>, boost::uint_<73>, boost::uint_<74>, boost::uint_<75>,
boost::uint_<76>, boost::uint_<77>, boost::uint_<78>, boost::uint_<79>, boost::uint_<80>,
        boost::uint_<81>, boost::uint_<82>, boost::uint_<83>, boost::uint_<84>, boost::uint_<85>,
boost::uint_<86>, boost::uint_<87>, boost::uint_<88>, boost::uint_<89>, boost::uint_<90>,
        boost::uint_<91>, boost::uint_<92>, boost::uint_<93>, boost::uint_<94>, boost::uint_<95>,
boost::uint_<96>, boost::uint_<97>, boost::uint_<98>, boost::uint_<99>, boost::uint_<100> > >'

 */