#include"operation.h"
#include"../symbolic/unit_test.h"

int main(){
	check_equal(2+x, x+2);
	check_equal(y+x, x+y);
	check_equal(-y+2, 2-y);
	check_equal(y-2, -2+y);
	check_equal(z+y+x, z+x+y);

	check_less(static_compare(math::add_operation_t{}, -y,-x), 0);
	check_equal(inverse(math::add_operation_t{}, (x+y)), -x-y);
	check_equal((x+y)+(x+y), x+y+x+y);
	check_equal((x+y)+(x+y), (x+x)+(y+y));

	return 0;
}

