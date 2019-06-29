#include"orientation.h"
#include"unit_test.h"

int main(){
	namespace hana=boost::hana;

	auto orientation=math::geometry::orientation_t{
		hana::make_tuple(Px,Py,Pz),
		hana::make_tuple(e1,e2,e3),
		math::geometry::simple_rotation_t{math::geometry::plane(e1,e2), math::ratio<1,2>*math::half_turn}
	};

	{
	check_equal(change_reference_frame(Px, to_linear_map(orientation)), -e2);
	check_equal(change_reference_frame(Py, to_linear_map(orientation)), e1);
	check_equal(change_reference_frame(Pz, to_linear_map(orientation)), e3);
	}

	{
	auto inverse_orientation=inverse(orientation);
	check_equal(change_reference_frame(e1, to_linear_map(inverse_orientation)), Py);
	check_equal(change_reference_frame(e2, to_linear_map(inverse_orientation)), -Px);
	check_equal(change_reference_frame(e3, to_linear_map(inverse_orientation)), Pz);
	}

	{
	auto rotation=math::geometry::simple_rotation_t{math::geometry::plane(e1,e3), math::ratio<1,2>*math::half_turn};
	check_equal(rotation(orientation), math::geometry::orientation_t{orientation.frame,orientation.reference_frame, (orientation.rotation_from_reference,rotation)});
	}

	return 0;
}

