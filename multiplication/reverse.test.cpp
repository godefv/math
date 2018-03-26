#include"reverse.h"
#include"../symbolic/unit_test.h"

int main(){
	using math::one;
	check_equal(reverse(x*y), y*x);
	check_equal(reverse(one+x*y), one+y*x);
	check_equal(reverse(2*x*y-6*y*x*z), 2*y*x-6*z*x*y);
	return 0;
}

