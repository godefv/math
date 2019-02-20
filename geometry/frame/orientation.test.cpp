#include"orientation.h"
#include"unit_test.h"

int main(){
	auto constexpr orientation1=math::geometry::orientation_t{boost::hana::make_map(
		 boost::hana::make_pair(Px, normalized(e1+e2))
		,boost::hana::make_pair(Py, normalized(e1-e2))
	)};

	check_equal(math::geometry::get_reference_frame(normalized(e1+e2)), boost::hana::make_set(e1,e2));
	check_equal(math::geometry::get_reference_frame(normalized(2.0*e1-4.0*e2)), boost::hana::make_set(e1,e2));
	
	check_equal(inverse(orientation1).vectors, boost::hana::make_map(
		 boost::hana::make_pair(e1, normalized(Px+Py))
		,boost::hana::make_pair(e2, normalized(Px-Py))
	));
	
	check_equal(change_reference_frame(Px+2.0*Py, orientation1), normalized(e1+e2)+2.0*normalized(e1-e2));
	
	return 0;
}

