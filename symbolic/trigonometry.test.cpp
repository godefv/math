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
	return 0;
}

