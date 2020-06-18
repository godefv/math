#include"differentiate.h"
#include"../symbolic/unit_test.h"


auto constexpr test_with_variable(math::Symbol auto variable){
	using math::ratio;
	using math::integer;

	check_equal(differentiate(variable, x*y), differentiate(variable, x)*y+x*differentiate(variable, y));
	check_equal(differentiate(variable, x*y*z), differentiate(variable, x)*y*z+x*differentiate(variable, y)*z+x*y*differentiate(variable, z));

	check_equal(differentiate(variable, square(k)), integer<2>*differentiate(variable, k)*k);
	check_equal(differentiate(variable, sqrt  (k)), ratio<1,2>*differentiate(variable, k)/sqrt(k));
}

int main(){
	test_with_variable(x);
	test_with_variable(y);
	test_with_variable(z);
	test_with_variable(k);
	test_with_variable(l);
	test_with_variable(m);

	return 0;
}

