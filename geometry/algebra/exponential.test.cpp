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

	std::cout<<"\ndouble\n"<<std::endl;
	//check_equal(exp(1.2*(e1+n1)*e2) , 1.+1.2*(e1+n1)*e2);
	check_equal(exp(1.2*e1*e2)      , eval(cos (1.2)+sin (1.2)*e1*e2));
	check_equal(exp(1.2*e1*n1)      , eval(cosh(1.2)+sinh(1.2)*e1*n1));

	std::cout<<"\ndouble times pi\n"<<std::endl;
	//check_equal(exp(1.2*pi*(e1+n1)*e2) , eval(1.+1.2*pi*(e1+n1)*e2));
	//check_equal(exp(1.2*pi*e1*e2)      , std::cos (1.2*eval(pi))+std::sin (1.2*eval(pi))*e1*e2);
	//check_equal(exp(1.2*pi*e1*n1)      , std::cosh(1.2*eval(pi))+std::sinh(1.2*eval(pi))*e1*n1);

	std::cout<<"\nsymbol times pi\n"<<std::endl;
	check_equal(exp(k*pi*(e1+n1)*e2) , one+k*pi*(e1+n1)*e2);
	//check_equal(exp(k*pi*e1*e2)      , cos(k*pi)+sin(k*pi)*e1*e2);
	//check_equal(exp(k*pi*e1*n1)      , cosh(k*pi)+sinh(k*pi)*e1*e2);

	return 0;
}

