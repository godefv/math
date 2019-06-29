#include"linear_map.h"
#include"unit_test.h"

int main(){
	namespace hana=boost::hana;

	auto constexpr linear_map1=math::geometry::linear_map_t{hana::make_map(
		 hana::make_pair(Px, normalized(e1+e2))
		,hana::make_pair(Py, normalized(e1-e2))
		,hana::make_pair(Pz, normalized(e3))
	)};

	check_equal(math::geometry::get_reference_frame(normalized(e1+e2)), hana::make_set(e1,e2));
	check_equal(math::geometry::get_reference_frame(normalized(2.0*e1-4.0*e2)), hana::make_set(e1,e2));
	
	check_equal(inverse(linear_map1).vectors, hana::make_map(
		 hana::make_pair(e1, normalized(Px+Py))
		,hana::make_pair(e2, normalized(Px-Py))
		,hana::make_pair(e3, normalized(Pz))
	));
	
	check_equal(change_reference_frame(Px+2.0*Py, linear_map1), normalized(e1+e2)+2.0*normalized(e1-e2));
	
	//transform a rotation relative to parent
	{
		auto constexpr rotation=math::geometry::simple_rotation_t{math::geometry::plane(e1,e2), math::ratio<1,2>*math::half_turn};

		check_equal(hana::keys  (rotation(linear_map1).vectors)|hana::to_tuple, hana::keys  (linear_map1.vectors)|hana::to_tuple);
		check_equal(hana::values(rotation(linear_map1).vectors)|hana::to_tuple, hana::values(linear_map1.vectors)|hana::transform_with(rotation)|hana::to_tuple);
	}

	//change frame : rotations
	{
		auto constexpr rotation_P=math::geometry::simple_rotation_t{math::geometry::plane(Px,Pz), math::ratio<1,2>*math::half_turn};
		auto constexpr rotation_e=math::geometry::simple_rotation_t{math::geometry::plane(normalized(e1+e2),e3), math::ratio<1,2>*math::half_turn};

		check_equal(change_reference_frame(rotation_P, linear_map1), rotation_e);
	}

	return 0;
}

