#include"placement.h"
#include"unit_test.h"

int main(){
	auto constexpr placement1=math::geometry::placement_t{
		 math::geometry::position_t{Po, math::geometry::point(O, 3.0*e1)}
		,math::geometry::orientation_t{boost::hana::make_map(
			 boost::hana::make_pair(Px, normalized(e1+e2))
			,boost::hana::make_pair(Py, normalized(e1-e2))
			,boost::hana::make_pair(Pz, normalized(e3))
		)}
	};
	auto inverse_placement1=inverse(placement1);

	check_equal(change_reference_frame(Po, placement1), placement1.position.value);
	check_equal(change_reference_frame(math::geometry::point(Po, Px), placement1), math::geometry::point(O, 3.0*e1+normalized(e1+e2)));
	check_equal(change_reference_frame(math::geometry::point(Po, Py), placement1), math::geometry::point(O, 3.0*e1+normalized(e1-e2)));
	check_equal(change_reference_frame(math::geometry::point(Po, 2.0*Px+4.0*Py), placement1), math::geometry::point(O, 3.0*e1+2.0*normalized(e1+e2)+4.0*normalized(e1-e2)));

	check_equal(change_reference_frame(O, inverse_placement1), math::geometry::point(Po, -3.0*normalized(Px+Py)));
	check_equal(change_reference_frame(math::geometry::point(O, e1), inverse_placement1), math::geometry::point(Po, -3.0*normalized(Px+Py)+normalized(Px+Py)));
	check_equal(change_reference_frame(math::geometry::point(O, e2), inverse_placement1), math::geometry::point(Po, -3.0*normalized(Px+Py)+normalized(Px-Py)));
	check_equal(change_reference_frame(math::geometry::point(O, 2.0*e1+4.0*e2), inverse_placement1), math::geometry::point(Po, -3.0*normalized(Px+Py)+2.0*normalized(Px+Py)+4.0*normalized(Px-Py)));

	//transform a placement relative to parent
	{
		auto constexpr translation=math::geometry::translation_t{e0};
		auto constexpr rotation=math::geometry::make_point_rotation(O, math::geometry::plane(e1,e2), math::ratio<1,2>*math::half_turn);

		check_equal(translation(placement1).orientation, placement1.orientation);
		check_equal(translation(placement1).position   , translation(placement1.position));
		check_equal(rotation(placement1).orientation, rotation.vector_transform(placement1.orientation));
		check_equal(rotation(placement1).position   , rotation(placement1.position));
	}

	//change frame : rotations
	{
		auto constexpr rotation_P=math::geometry::make_point_rotation(Po, math::geometry::plane(Px,Pz), math::ratio<1,2>*math::half_turn);
		auto constexpr rotation_e=math::geometry::make_point_rotation(math::geometry::point(O, 3.0*e1), math::geometry::plane(normalized(e1+e2),e3), math::ratio<1,2>*math::half_turn);

		check_equal(change_reference_frame(rotation_P, placement1), rotation_e);
	}

	return 0;
}

