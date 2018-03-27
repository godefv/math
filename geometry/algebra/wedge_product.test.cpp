#include"wedge_product.h"
#include"unit_test.h"

int main(){
	using math::one;
	using math::zero;

	check_equal(e1^e1, zero);
	check_equal(e1^e2, e1*e2);
	check_equal(e1^n1, e1*n1);
	check_equal(e1^(e2+e1), e1*e2);
	return 0;
}

