#include"operation.h"
#include"../symbolic/unit_test.h"

int main(){
	using math::integer;
	//scalars commute
	check_equal(2*x, x*2);
	check_equal(integer<2>*x, x*integer<2>);
	check_equal(inverse(y)*2, 2/y);
	check_equal(y/2, 0.5*y);

	//develop over addition
	check_equal(2*(x+y), 2*x+2*y);
	check_equal(z*(x+y), z*x+z*y);
	check_equal(y*(x+y), y*x+y*y);

	//multiplying by zero gives zero
	check_equal(2*math::zero, math::zero);
	check_equal(math::zero*2, math::zero);
	check_equal(x*math::zero, math::zero);
	check_equal(math::zero*x, math::zero);

	//generate powers
	using math::group::power;
	check_equal(power(math::mult_operation_t{}, integer<2>, x),x*x);
	check_equal(power(math::mult_operation_t{}, integer<3>, x),x*power(math::mult_operation_t{}, integer<2>, x));
	check_equal(power(math::mult_operation_t{}, integer<3>, x),power(math::mult_operation_t{}, integer<2>, x)*x);
	check_equal(power(math::mult_operation_t{}, integer<5>, x),power(math::mult_operation_t{}, integer<2>, x)*power(math::mult_operation_t{}, integer<3>, x));
	check_equal(power(math::mult_operation_t{}, integer<6>, x),x*x*x*x*x*x);

	//addition nth power of x equals n*x
	check_equal(x+x, math::integer<2>*x);
	check_equal(x+x+x, math::integer<3>*x);
	check_equal(x+y+x, math::integer<2>*x+y);
	check_equal(math::Symbol<decltype(x*x)>, true);
	check_equal(x*x+x*x, math::integer<2>*x*x);

	return 0;
}

