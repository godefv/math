#include"operation/all.h"
#include"rational.h"
#include"unit_test.h"
#include"../multiplication/operation.h"
#include"../multiplication/power.h"

int main(){
	using namespace godefv::math;

	//concepts
	check_equal(Scalar<decltype(cos(2))>, true);
	check_equal(Symbol<decltype(cos(2))>, false);
	check_equal(Scalar<decltype(cos(x))>, false);
	check_equal(Symbol<decltype(cos(x))>, true);

	//commutation
	check_equal(cos(2)*sin(2)                 , sin(2)*cos(2)                 );
	check_equal(cos(2)*sqrt(2)                , sqrt(2)*cos(2)                );
	check_equal(pow<2>(cos(2))*sqrt(2)        , sqrt(2)*pow<2>(cos(2))        );
	check_equal(cos(2)*sqrt(3)*cos(2)*sqrt(2) , cos(2)*cos(2)*sqrt(3)*sqrt(2) );
	check_equal(cos(integer<2>)*sqrt(3)*cos(integer<2>)*sqrt(integer<2>), cos(integer<2>)*cos(integer<2>)*sqrt(3)*sqrt(integer<2>));
	check_equal(cosh(integer<2>)+sinh(integer<2>), sinh(integer<2>)+cosh(integer<2>));
	check_equal(pow<2>(cosh(integer<2>))-pow<2>(sinh(integer<2>)), -pow<2>(sinh(integer<2>))+pow<2>(cosh(integer<2>)));

	//abs is a morphism over addition, except it applies on addition exponent
	check_equal(abs(-x), abs(x));
	check_equal(abs(x+y), abs(x)+abs(y));
	check_equal(abs(-x+y), abs(x)+abs(y));
	check_equal(abs(2*x-y), 2*abs(x)+abs(y));
	//abs is a morphism over multiplication
	check_equal(abs(x*y), abs(x)*abs(y));
	check_equal(abs(nth_root<2>(x)), nth_root<2>(abs(x)));
	//abs is a morphism over both addition and multiplication, except it applies on addition exponent
	check_equal(abs(-2*x), 2*abs(x));
	check_equal(abs(4*x*(-y)-x-2*y), 4l*abs(x)*abs(y)+abs(x)+2l*abs(y));
	check_equal(abs(-one), one);

	//reverse of exp is exp of reverse
	check_equal(reverse(exp(x*y)), exp(y*x));

	//formatting
	std::cout<<exp(integer<3>)<<std::endl;
	std::cout<<cos(integer<3>)<<std::endl;
	std::cout<<square(cos(sqrt(integer<5>)))<<std::endl;

	return 0;
}

