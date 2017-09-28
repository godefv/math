#include"trigonometry.h"
#include"../unit_test.h"

int main(){
	using namespace symbolic;
	check_equal(sin(angle_t<ratio_t<0,2>>{}), integer<0>);
	check_equal(sin(angle_t<ratio_t<1,2>>{}), integer<1>);
	check_equal(sin(angle_t<ratio_t<2,2>>{}), integer<0>);
	check_equal(sin(angle_t<ratio_t<3,2>>{}), integer<-1>);
	check_equal(sin(angle_t<ratio_t<4,2>>{}), integer<0>);
	check_equal(sin(angle_t<ratio_t<5,2>>{}), integer<1>);
	check_equal(sin(angle_t<ratio_t<6,2>>{}), integer<0>);
	check_equal(sin(angle_t<ratio_t<7,2>>{}), integer<-1>);
	check_equal(sin(angle_t<ratio_t<8,2>>{}), integer<0>);
	return 0;
}

