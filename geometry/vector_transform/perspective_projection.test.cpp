#include"perspective_projection.h"
#include"../algebra/unit_test.h"

int main(){
	using math::integer;
	using math::ratio;
	auto constexpr projection1=math::geometry::perspective_projection_t{e2, ratio<1,10>};
	auto constexpr projection2=math::geometry::perspective_projection_t{normalized(e0-e1), ratio<1,10>};
	auto constexpr projection3=math::geometry::perspective_projection_t{normalized(2.0*e0-2.0*e1), 0.1};

	check_equal(projection1(e0), math::infinity*e0);
	check_equal(projection1(e1), math::infinity*e1);
	check_equal(projection1(e2), math::zero);
	check_equal(projection1(2.0*e0+4.0*e2), 0.5*e0);
	check_equal(projection1(2.0*e0-4.0*e2), std::numeric_limits<double>::infinity()*e0); 
	check_equal(projection2(e0), ratio<1,2>*sqrt(integer<2>)*(e0+e1));
	check_equal(projection2(e1), ratio<1,2>*math::infinity*(e0+e1));
	check_equal(projection2(e2), math::infinity*e2);
	//check_equal(projection3(e0), );
	//check_equal(projection3(e1), );
	check_equal(projection3(e2), std::numeric_limits<double>::max()*e2);

	return 0;
}

