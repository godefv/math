#include"operation.h"
#include"../symbolic/unit_test.h"

auto constexpr operator+(y_t,z_t){return k;}
auto constexpr operator+(y_t,math::minus_t<z_t>){return m;}


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
	check_equal(integer<4>*(2.0*x), 8.0*x);

	//develop over addition
	check_equal(2*(x+y), 2*x+2*y);
	check_equal(z*(x+y), z*x+z*y);
	check_equal(y*(x+y), y*x+y*y);
	check_equal((x+y)*z, x*z+y*z);
	check_equal((1+3*x)*(1+3*x), 1+6*x+9*x*x);
	//check_equal((z+y)*(x+y), z*x+z*y+y*x+y*y);

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
	check_equal(power(math::mult_operation_t{}, math::ratio<1,2>, integer<3>)*math::ratio<1,2>, math::ratio<1,2>*power(math::mult_operation_t{}, math::ratio<1,2>, integer<3>));

	//addition nth power of x equals n*x
	check_equal(x+x, math::integer<2>*x);
	check_equal(x+x+x, math::integer<3>*x);
	check_equal(x+y+x, math::integer<2>*x+y);
	check_equal(math::Symbol<decltype(x*x)>, true);
	check_equal(x*x+x*x, math::integer<2>*x*x);

	//contract ab+ac=a(b+c) if (b+c) can be processed
	check_equal(x*y+x*z, k*x);
	check_equal(x*z+x*y, k*x);
	//contract ac+bc=(a+b)c if (a+b) can be processed
	check_equal(integer<2>*x+integer<5>*x, integer<7>*x);
	check_equal(y*x+z*x, k*x);
	check_equal(z*x+y*x, k*x);
	//contract ab+kac=a(b+kc) if (b+kc) can be processed
	//check_equal(x*y+l*x*z, m*x);
	//contract ac+kbc=(a+kb)c if (a+kb) can be processed
	check_equal(y*x+(-z*x), m*x);
	check_equal(y*x-z*x, m*x);
	
	//commutation
	check_equal(static_compare(math::add_operation_t{}, x*y, y*z)>0, true);
	check_equal(x*y+y*z+x*y, math::integer<2>*x*y+y*z);
	check_equal(-math::integer<2>*x*y+-math::integer<2>*y*z+math::integer<2>*x*y, -math::integer<2>*y*z);

	//eval
	check_equal(eval_with_data(x*y+z, [](auto symbol){return eval_symbol(symbol);}), eval_symbol(x)*eval_symbol(y)+eval_symbol(z));

	return 0;
}

