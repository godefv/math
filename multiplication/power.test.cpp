#include"power.h"
#include"../symbolic/unit_test.h"

int main(){
	using math::pow;
	using math::nth_root;
	using math::integer;
	using math::ratio;

	//concepts
	check_equal(math::group::Power<math::mult_operation_t, decltype(math::group::power(math::mult_operation_t{}, ratio<1,3>, integer<2>))>, true);

	//powers of rationals
	check_equal(pow<3>(integer<2>),integer<8>);
	check_equal(nth_root<3>(integer<8>),integer<2>);
	check_equal(nth_root<2>(integer<25>), integer<5>);
	check_equal(nth_root<2>(integer<4>), integer<2>);
	check_equal(nth_root<2>(integer<2>)*nth_root<2>(integer<2>), integer<2>);

	//special powers
	check_equal(pow<1>(x),x);
	check_equal(pow<2>(x),x*x);

	//power of power
	check_equal(pow<4>(nth_root<3>(x)), pow(x, ratio<4,3>));
	check_equal(pow<4>(nth_root<2>(x)), pow<2>(x));

	//multiplication power of addition power (ka)^n = (k^n)(a^n) because k is a scalar
	check_equal(pow<2>(x+x),x*x+x*x+x*x+x*x);
	check_equal(pow<-1>(-x),-pow<-1>(x));

	//formatting
	std::cout<<"\nformatting:\n"<<std::endl;
	std::cout<<nth_root<2>(x)<<std::endl;
	std::cout<<nth_root<3>(x)<<std::endl;
	std::cout<<nth_root<4>(x)<<std::endl;
	std::cout<<nth_root<5>(x)<<std::endl;
	std::cout<<pow<2>(x)<<std::endl;
	std::cout<<pow<3>(x)<<std::endl;
	std::cout<<pow<4>(x)<<std::endl;
	std::cout<<pow<5>(x)<<std::endl;
	std::cout<<pow(x, ratio<2,5>)<<std::endl;

	return 0;
}

