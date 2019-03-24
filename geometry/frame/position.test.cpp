#include"position.h"
#include"unit_test.h"

int main(){
	auto constexpr position1=math::geometry::position_t{Po, math::geometry::point(O, 3.0*e1)};

	//transform a position relative to parent
	auto constexpr translation1=math::geometry::translation_t{e0};
	auto constexpr rotation1=math::geometry::make_point_rotation(O, math::geometry::plane(e1,e2), math::ratio<1,2>*math::half_turn);
	auto constexpr rotation2=math::geometry::make_point_rotation(Po, math::geometry::plane(e1,e2), math::ratio<1,2>*math::half_turn);

	check_equal(translation1(position1).key  , position1.key);
	check_equal(translation1(position1).value, translation1(position1.value));
	check_equal(rotation1(position1).key  , position1.key);
	check_equal(rotation1(position1).value, rotation1(position1.value));
	check_equal(rotation2(position1).key  , position1.key);
	check_equal(rotation2(position1).value, position1.value);

	return 0;
}

