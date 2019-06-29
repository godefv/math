#include"placement.h"
#include"unit_test.h"

int main(){
	namespace hana=boost::hana;

	auto placement=math::geometry::placement_t{
		 math::geometry::position_t{Po, math::geometry::point(O, 3.0*e1)}
		,math::geometry::orientation_t{
			hana::make_tuple(Px,Py,Pz),
			hana::make_tuple(e1,e2,e3),
			math::geometry::simple_rotation_t{math::geometry::plane(e1,e2), math::ratio<1,2>*math::half_turn}
		}
	};

	{
	check_equal(change_reference_frame(math::geometry::point(Po, 1.0*Px), to_affine_map(placement)), math::geometry::point(placement.position.value, -1.0*e2));
	check_equal(change_reference_frame(math::geometry::point(Po, 1.0*Py), to_affine_map(placement)), math::geometry::point(placement.position.value,  1.0*e1));
	check_equal(change_reference_frame(math::geometry::point(Po, 1.0*Pz), to_affine_map(placement)), math::geometry::point(placement.position.value,  1.0*e3));
	}

	{
	auto inverse_placement=inverse(placement);
	check_equal(change_reference_frame(math::geometry::point(placement.position.value, -1.0*e2), to_affine_map(inverse_placement)), math::geometry::point(Po, 1.0*Px+0.0*Py));
	check_equal(change_reference_frame(math::geometry::point(placement.position.value,  1.0*e1), to_affine_map(inverse_placement)), math::geometry::point(Po, 1.0*Py));
	check_equal(change_reference_frame(math::geometry::point(placement.position.value,  1.0*e3), to_affine_map(inverse_placement)), math::geometry::point(Po, 1.0*Pz+0.0*Py));
	}

	{
	auto vector_transform=math::geometry::simple_rotation_t{math::geometry::plane(e1,e3), math::ratio<1,2>*math::half_turn};
	auto rotation=make_point_transform(placement.position.value, vector_transform);
	check_equal(rotation(placement), math::geometry::placement_t{
		 math::geometry::position_t{placement.position.key, rotation(placement.position.value)}
		,vector_transform(placement.orientation)
	});
	}

	{
	auto vector_transform=math::geometry::simple_rotation_t{math::geometry::plane(e1,e3), math::ratio<1,2>*math::half_turn};
	auto rotation=make_point_transform(O, vector_transform);
	check_equal(rotation(placement), math::geometry::placement_t{
		 math::geometry::position_t{placement.position.key, rotation(placement.position.value)}
		,vector_transform(placement.orientation)
	});
	}

	return 0;
}

