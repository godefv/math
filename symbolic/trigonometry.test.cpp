#include"trigonometry.h"
#include"unit_test.h"

using namespace math;

auto f(Symbol){}
auto constexpr theta="θ"_symbol;
using theta_t=std::decay_t<decltype(theta)>;
namespace math{
	template<> struct is_vector<pi_t,theta_t>:std::true_type {};
}

int main(){
	using namespace math;
	//concepts
	check_equal(Symbol<decltype(ratio<1,4>*half_turn)>, true);
	check_equal(Symbol<decltype(sinh(ratio<1,4>*half_turn))>, true);
	check_equal(Symbol<decltype(sinh(x))>, true);
	check_equal(Symbol<decltype(k*pi)>, true);
	check_equal(Angle<pi_t>, true);
	check_equal(Angle<angle_t<ratio_t<1,4>>>, true);
	check_equal(Angle<decltype(k*pi)>, true);
	check_equal(Angle<theta_t>, true);
	check_equal(Angle<integer_t<3>>, false);
	check_equal(Angle<double>, false);

	//first quadrant exact values
	check_equal(sin(ratio<0,2>*half_turn), integer<0>);
	check_equal(sin(ratio<1,2>*half_turn), integer<1>);
	check_equal(sin(ratio<2,2>*half_turn), integer<0>);
	check_equal(sin(ratio<3,2>*half_turn), integer<-1>);
	check_equal(sin(ratio<4,2>*half_turn), integer<0>);
	check_equal(sin(ratio<5,2>*half_turn), integer<1>);
	check_equal(sin(ratio<6,2>*half_turn), integer<0>);
	check_equal(sin(ratio<7,2>*half_turn), integer<-1>);
	check_equal(sin(ratio<8,2>*half_turn), integer<0>);
	check_equal(sin(ratio<1,3>*half_turn), ratio<1,2>*sqrt(integer<3>));
	std::cout<<cos(ratio<1,5>*half_turn)<<std::endl;
	std::cout<<cos(ratio<3,5>*half_turn)<<std::endl;
	std::cout<<sin(ratio<5,12>*half_turn)<<std::endl;
	
	//cos²+sin²=1
	check_equal(square(cos(ratio<3,7>*half_turn))+square(sin(ratio<3,7>*half_turn)), integer<1>);
	check_equal(square(cos(k*pi))+square(sin(k*pi)), integer<1>);
	check_equal(square(sin(k*pi))+square(cos(k*pi)), integer<1>);
	check_equal(integer<5>*square(cos(k*pi))+integer<5>*square(sin(k*pi)), integer<5>);
	check_equal(x*square(cos(k*pi))+x*square(sin(k*pi)), x);
	check_equal(square(cos(k*pi))*x+square(sin(k*pi))*x, x);
	check_equal(integer<2>*x*square(cos(k*pi))+integer<2>*x*square(sin(k*pi)), integer<2>*x);

	//ch²-sh²=1
	check_equal(square(cosh(k*pi))-square(sinh(k*pi)), integer<1>);
	check_equal(-square(sinh(k*pi))+square(cosh(k*pi)), integer<1>);
	check_equal(integer<5>*square(cosh(k*pi))-integer<5>*square(sinh(k*pi)), integer<5>);
	check_equal(x*square(cosh(k*pi))-x*square(sinh(k*pi)), x);
	check_equal(square(cosh(k*pi))*x-square(sinh(k*pi))*x, x);
	check_equal(integer<2>*x*square(cosh(k*pi))-integer<2>*x*square(sinh(k*pi)), integer<2>*x);

	return 0;
}

