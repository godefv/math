#include"operation.h"
#include"../symbolic/unit_test.h"

auto constexpr operator+(y_t,z_t){return k;}


int main(){
	using math::integer;
	//inverse
	check_equal(inverse(inverse(x)), x);
	check_equal(x*inverse(x), math::one);
	check_equal(inverse(x)*x, math::one);

	//scalars commute
	check_equal(2*x, x*2);
	check_equal(integer<2>*x, x*integer<2>);
	check_equal(inverse(y)*2, 2/y);
	check_equal(y/2, 0.5*y);
	check_equal(x*(-y), -(x*y));

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

	//contract ac+bc=(a+b)c if (a+b) can be processed
	check_equal(integer<2>*x+integer<5>*x, integer<7>*x);
	check_equal(y*x+z*x, k*x);
	check_equal(z*x+y*x, k*x);
	//contract ab+ac=a(b+c) if (b+c) can be processed
	check_equal(x*y+x*z, k*x);
	check_equal(x*z+x*y, k*x);
	
	return 0;
}

