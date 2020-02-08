#include"rational.h"
#include"constant.h"
#include"../unit_test.h"

int main(){
	using namespace godefv::math;
	check_equal(ratio<2,3>*ratio<2,3>, ratio<4,9>);
	check_equal(integer<0>*ratio<2,3>, integer<0>);
	check_equal(integer<0>*2.4, integer<0>);
	check_equal(integer<0>/2.4, integer<0>);
	check_equal(inverse(ratio<2,3>), ratio<3,2>);
	check_equal(eval(ratio<1,4>), 0.25);
	check_equal(sqrt(ratio<1,4>), ratio<1,2>);
	check_equal(sqrt(ratio<144,25>), ratio<12,5>);

	check_equal(2.0*ratio<1,8>, 0.25);

	check_equal(pi>=integer<0>, std::true_type{});

	static_assert(Symbol<ratio_t<1,4>>);
	
	return 0;
}

