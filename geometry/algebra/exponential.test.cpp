#include"exponential.h"
#include"unit_test.h"

int main(){
	using math::geometry::exp;
	using math::ratio;
	using math::one;
	using math::pi;

	check_equal(exp(ratio<1,4>*pi*(e1+n1)*e2) , one+ratio<1,4>*pi*(e1+n1)*e2);
	check_equal(exp(ratio<1,4>*pi*e1*e2)      , cos (ratio<1,4>*pi)+sin (ratio<1,4>*pi)*e1*e2);
	check_equal(exp(ratio<1,4>*pi*e1*n1)      , cosh(ratio<1,4>*pi)+sinh(ratio<1,4>*pi)*e1*n1);

	check_equal(exp(ratio<3,13>*pi*(e1+n1)*e2), one+ratio<3,13>*pi*(e1+n1)*e2);
	check_equal(exp(ratio<3,13>*pi*e1*e2)     , cos (ratio<3,13>*pi)+sin (ratio<3,13>*pi)*e1*e2);
	check_equal(exp(ratio<3,13>*pi*e1*n1)     , cosh(ratio<3,13>*pi)+sinh(ratio<3,13>*pi)*e1*n1);

	check_equal(exp(k*pi*(e1+n1)*e2) , one+k*pi*(e1+n1)*e2);
	//check_equal(exp(k*pi*e1*e2)      , cos(k*pi)+sin(k*pi)*e1*e2);
	//check_equal(exp(k*pi*e1*n1)      , cosh(k*pi)+sinh(k*pi)*e1*e2);

	return 0;
}

