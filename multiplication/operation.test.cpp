#include"operation.h"
#include"../symbolic/unit_test.h"

int main(){
	//scalars commute
	check_equal(2*x, x*2);
	check_equal(math::integer<2>*x, x*math::integer<2>);
	check_equal(inverse(y)*2, 2/y);
	check_equal(y/2, 0.5*y);

	//develop over addition
	check_equal(2*(x+y), 2*x+2*y);
	check_equal(z*(x+y), z*x+z*y);
	check_equal(y*(x+y), y*x+y*y);

	//multiplying by zero gives zero
	check_equal(2*math::zero, math::zero);
	check_equal(math::zero*2, math::zero);
	check_equal(x*math::zero, math::zero);
	check_equal(math::zero*x, math::zero);

	//addition nth power of x equals n*x
	check_equal(x+x, math::integer<2>*x);
	check_equal(x+x+x, math::integer<3>*x);
	check_equal(x+y+x, math::integer<2>*x+y);

	return 0;
}

