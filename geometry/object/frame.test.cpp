#include"frame.h"
#include"../algebra/norm.h"
#include"../algebra/unit_test.h"

using namespace math::geometry::literals;
static constexpr auto X="X"_direction_positive; 
static constexpr auto Y="Y"_direction_positive; 

int main(){
	auto constexpr frame_xy=math::geometry::orientation_t{boost::hana::make_map(
		 boost::hana::make_pair(X, normalized(e1+e2))
		,boost::hana::make_pair(Y, normalized(e1-e2))
	)};
	check_equal(math::geometry::get_frame(normalized(e1+e2)), boost::hana::make_set(e1,e2));
	check_equal(math::geometry::get_frame(normalized(2.0*e1-4.0*e2)), boost::hana::make_set(e1,e2));
	check_equal(inverse(frame_xy).vectors, boost::hana::make_map(
		 boost::hana::make_pair(e1, normalized(X+Y))
		,boost::hana::make_pair(e2, normalized(X-Y))
	));
	return 0;
}

