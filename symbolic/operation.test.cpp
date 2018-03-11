#include"operation/all.h"
#include"rational.h"

using x_t=symbolic::symbol_t<struct x_symbol_name_t>; 
x_t x;
inline bool operator==(x_t,x_t){return true;}
inline bool operator!=(x_t,x_t){return false;}
inline std::ostream& operator<<(std::ostream& out,x_t){return out<<"x";}

int main(){
	using namespace symbolic;
	check_equal(x,x);

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

	static_assert(Symbol<decltype(nth_root<2>(x))>);

	return 0;
}

