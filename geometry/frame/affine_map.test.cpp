#include"affine_map.h"
#include"unit_test.h"

int main(){
	auto constexpr affine_map1=math::geometry::affine_map_t{
		 math::geometry::position_t{Po, math::geometry::point(O, 3.0*e1)}
		,math::geometry::linear_map_t{boost::hana::make_map(
			 boost::hana::make_pair(Px, normalized(e1+e2))
			,boost::hana::make_pair(Py, normalized(e1-e2))
			,boost::hana::make_pair(Pz, normalized(e3))
		)}
	};
	auto inverse_affine_map1=inverse(affine_map1);

	check_equal(change_reference_frame(Po, affine_map1), affine_map1.origin_map.value);
	check_equal(change_reference_frame(math::geometry::point(Po, Px), affine_map1), math::geometry::point(O, 3.0*e1+normalized(e1+e2)));
	check_equal(change_reference_frame(math::geometry::point(Po, Py), affine_map1), math::geometry::point(O, 3.0*e1+normalized(e1-e2)));
	check_equal(change_reference_frame(math::geometry::point(Po, 2.0*Px+4.0*Py), affine_map1), math::geometry::point(O, 3.0*e1+2.0*normalized(e1+e2)+4.0*normalized(e1-e2)));

	check_equal(change_reference_frame(O, inverse_affine_map1), math::geometry::point(Po, -3.0*normalized(Px+Py)));
	check_equal(change_reference_frame(math::geometry::point(O, e1), inverse_affine_map1), math::geometry::point(Po, -3.0*normalized(Px+Py)+normalized(Px+Py)));
	check_equal(change_reference_frame(math::geometry::point(O, e2), inverse_affine_map1), math::geometry::point(Po, -3.0*normalized(Px+Py)+normalized(Px-Py)));
	check_equal(change_reference_frame(math::geometry::point(O, 2.0*e1+4.0*e2), inverse_affine_map1), math::geometry::point(Po, -3.0*normalized(Px+Py)+2.0*normalized(Px+Py)+4.0*normalized(Px-Py)));

	//transform a affine_map relative to parent
	{
		auto constexpr translation=math::geometry::translation_t{e0};
		auto constexpr rotation=math::geometry::make_point_rotation(O, math::geometry::plane(e1,e2), math::ratio<1,2>*math::half_turn);

		check_equal(translation(affine_map1).directions_map, affine_map1.directions_map);
		check_equal(translation(affine_map1).origin_map   , translation(affine_map1.origin_map));
		check_equal(rotation(affine_map1).directions_map, rotation.vector_transform(affine_map1.directions_map));
		check_equal(rotation(affine_map1).origin_map   , rotation(affine_map1.origin_map));
	}

	//change frame : rotations
	{
		auto constexpr rotation_P=math::geometry::make_point_rotation(Po, math::geometry::plane(Px,Pz), math::ratio<1,2>*math::half_turn);
		auto constexpr rotation_e=math::geometry::make_point_rotation(math::geometry::point(O, 3.0*e1), math::geometry::plane(normalized(e1+e2),e3), math::ratio<1,2>*math::half_turn);

		check_equal(change_reference_frame(rotation_P, affine_map1), rotation_e);
	}

	return 0;
}

