#include"rational.h"
#include"../unit_test.h"

int main(){
	using namespace symbolic;
	check_equal(ratio<2,3>*ratio<2,3>, ratio<4,9>);
	check_equal(inverse(ratio<2,3>), ratio<3,2>);
	check_equal(eval(ratio<1,4>), 0.25);
	check_equal(abs(ratio<1,4>), ratio<1,4>);
	check_equal(sqrt(ratio<1,4>), ratio<1,2>);
	check_equal(sqrt(ratio<144,25>), ratio<12,5>);
	
	return 0;
}

