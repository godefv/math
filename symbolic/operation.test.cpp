#include"operation/all.h"
#include"rational.h"
#include"unit_test.h"

int main(){
	using namespace symbolic;
	check_equal(x,x);

	static_assert(Symbol<decltype(nth_root<2>(x))>);
	static_assert(Symbol<decltype(x*x)>);
	static_assert(group::Generated<mult_operation_t,decltype(x*y)>);
	static_assert(Symbol<decltype(x*y)>);

	//operation order
	check_less(static_compare(pow<2>(x), pow<3>(x)), 0);
	check_less(static_compare(sin(x), cos(x)), 0);
	check_less(static_compare(pow<2>(sin(x)), pow<2>(cos(x))), 0);
	check_less(static_compare(sqrt(y), cos(x)), 0);

	//multiplication
	unused((x*y)*(y*x));
	check_equal(cos(x),cos(x));
	check_equal(cos(x)*sqrt(y)*cos(x)*sqrt(x), cos(x)*cos(x)*sqrt(y)*sqrt(x));

	//pow
	check_equal(pow<3>(integer<2>),integer<8>);
	check_equal(nth_root<3>(integer<8>),integer<2>);
	check_equal(nth_root<2>(integer<25>), integer<5>);
	check_equal(nth_root<2>(integer<4>), integer<2>);
	check_equal(nth_root<2>(integer<2>)*nth_root<2>(integer<2>), integer<2>);
	check_equal(pow<1>(x),x);
	check_equal(pow<2>(x),x*x);
	check_equal(pow<4>(nth_root<3>(x)), pow<ratio_t<4,3>>(x));
	check_equal(pow<4>(nth_root<2>(x)), pow<2>(x));

	check_equal(inverse(x)*x,integer<1>);
	check_equal(abs(nth_root<2>(x)), nth_root<2>(abs(x)));

	//formatting
	std::cout<<exp(integer<3>)<<std::endl;
	std::cout<<sin(integer<3>)<<std::endl;
	std::cout<<nth_root<2>(integer<5>)<<std::endl;
	std::cout<<nth_root<3>(integer<5>)<<std::endl;
	std::cout<<nth_root<4>(integer<5>)<<std::endl;
	std::cout<<nth_root<5>(integer<5>)<<std::endl;
	std::cout<<pow<2>(integer<5>)<<std::endl;
	std::cout<<pow<3>(integer<5>)<<std::endl;
	std::cout<<pow<4>(integer<5>)<<std::endl;
	std::cout<<pow<5>(integer<5>)<<std::endl;
	std::cout<<pow<ratio_t<2,5>>(integer<5>)<<std::endl;
	std::cout<<square(sin(sqrt(integer<5>)))<<std::endl;
	using namespace symbolic::operators;
	std::cout<<-exp(integer<5>)<<std::endl;

	return 0;
}

