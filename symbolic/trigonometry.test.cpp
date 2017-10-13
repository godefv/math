#include"trigonometry.h"
#include"../unit_test.h"

int main(){
	using namespace symbolic;
	check_equal(sin(ratio<0,2>*half_turn), integer<0>);
	check_equal(sin(ratio<1,2>*half_turn), integer<1>);
	check_equal(sin(ratio<2,2>*half_turn), integer<0>);
	check_equal(sin(ratio<3,2>*half_turn), integer<-1>);
	check_equal(sin(ratio<4,2>*half_turn), integer<0>);
	check_equal(sin(ratio<5,2>*half_turn), integer<1>);
	check_equal(sin(ratio<6,2>*half_turn), integer<0>);
	check_equal(sin(ratio<7,2>*half_turn), integer<-1>);
	check_equal(sin(ratio<8,2>*half_turn), integer<0>);

	check_equal(sin(ratio<1,3>*half_turn), vector::basis_element_t{sqrt(integer<3>), ratio<1,2>});
	std::cout<<cos(ratio<1,5>*half_turn)<<std::endl;
	std::cout<<cos(ratio<3,5>*half_turn)<<std::endl;
	std::cout<<sin(ratio<5,12>*half_turn)<<std::endl;
	return 0;
}

