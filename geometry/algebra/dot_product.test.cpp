#include"dot_product.h"
#include"unit_test.h"

int main(){
	using math::one;
	using math::zero;

	check_equal(e1|e1, one);
	check_equal(e1|e2, zero);
	check_equal(e1|n1, zero);
	check_equal(e1|(e2+e1), one);
	check_equal((e1*e2)|(e1*e2), -one);
	check_equal((1.0f*e1+2.0f*e2+3.0f*e3)|(0.0f*e1+0.0f*e2+1.0f*e3), 3.0f);
	return 0;
}

