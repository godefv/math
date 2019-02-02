#include"projection.h"
#include"../algebra/unit_test.h"

int main(){
	using math::integer;
	auto constexpr projection1=math::geometry::projection_t{math::geometry::slice_t{e0}};
	auto constexpr projection2=math::geometry::projection_t{math::geometry::slice_t{integer<2>*e0+integer<2>*e1,e2}};
	auto constexpr projection3=math::geometry::projection_t{math::geometry::slice_t{2.0*e0+2.0*e1,8.0*e2}};

	check_equal(projection1(e0), e0);
	check_equal(projection1(e1), math::zero);
	check_equal(projection1(2.0*e2), math::zero);
	check_equal(projection1(2.0*e0-4.0*e1), 2.0*e0);
	check_equal(projection2(e0), math::ratio<1,2>*(e0+e1));
	check_equal(projection2(e1), math::ratio<1,2>*(e0+e1));
	check_equal(projection2(e2), e2);
	check_equal(projection3(e0), 0.5*e0+0.5*e1);
	check_equal(projection3(e1), 0.5*e0+0.5*e1);
	check_equal(projection3(e2), 1.0*e2);
	check_equal(projection3(n1), math::zero);

	return 0;
}

