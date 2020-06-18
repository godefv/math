#include"rational.h"
#include"constant.h"
#include"../unit_test.h"

int main(){
	using namespace godefv::math;
	//x*0=0
	check_equal(integer<0>*ratio<2,3>, integer<0>);
	check_equal(integer<0>*2.4, integer<0>);
	check_equal(integer<0>/2.4, integer<0>);
	//
	check_equal(ratio<2,3>*ratio<2,3>, ratio<4,9>);
	check_equal(inverse(ratio<2,3>), ratio<3,2>);
	check_equal(eval(ratio<1,4>), 0.25);
	check_equal(sqrt(ratio<1,4>), ratio<1,2>);
	check_equal(sqrt(ratio<144,25>), ratio<12,5>);

	//1*x=x without changing the type of x
	check_equal(integer<1>*2.4 , 2.4 );
	check_equal(integer<1>*2.4f, 2.4f);
	check_equal(integer<1>*2   , 2   );
	check_equal(integer<1>*std::numeric_limits<std::intmax_t>::max(), std::numeric_limits<std::intmax_t>::max());

	check_equal(2.0*ratio<1,8>, 0.25);

	check_equal(pi>=integer<0>, std::true_type{});

	static_assert(Symbol<ratio_t<1,4>>);
	static_assert(PositiveScalar<integer_t<2>>);
	static_assert(!PositiveScalar<int>);
	
	return 0;
}

