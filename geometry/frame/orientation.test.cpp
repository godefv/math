#include"orientation.h"
#include"unit_test.h"

int main(){
	namespace hana=boost::hana;

	auto constexpr orientation1=math::geometry::orientation_t{hana::make_map(
		 hana::make_pair(Px, normalized(e1+e2))
		,hana::make_pair(Py, normalized(e1-e2))
	)};

	check_equal(math::geometry::get_reference_frame(normalized(e1+e2)), hana::make_set(e1,e2));
	check_equal(math::geometry::get_reference_frame(normalized(2.0*e1-4.0*e2)), hana::make_set(e1,e2));
	
	check_equal(inverse(orientation1).vectors, hana::make_map(
		 hana::make_pair(e1, normalized(Px+Py))
		,hana::make_pair(e2, normalized(Px-Py))
	));
	
	check_equal(change_reference_frame(Px+2.0*Py, orientation1), normalized(e1+e2)+2.0*normalized(e1-e2));
	
	//transform a rotation relative to parent
	auto constexpr rotation1=math::geometry::simple_rotation_t{math::geometry::plane(e1,e2), math::ratio<1,2>*math::half_turn};

	check_equal(hana::keys  (rotation1(orientation1).vectors)|hana::to_tuple, hana::keys  (orientation1.vectors)|hana::to_tuple);
	check_equal(hana::values(rotation1(orientation1).vectors)|hana::to_tuple, hana::values(orientation1.vectors)|hana::transform_with(rotation1)|hana::to_tuple);

	return 0;
}

