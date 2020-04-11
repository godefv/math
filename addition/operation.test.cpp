#include"operation.h"
#include"power.h"
#include"../group/unit_test.h"

int main(){
	//commutation
	check_equal(2+x, x+2);
	check_equal(y+x, x+y);
	check_equal(-y+2l, 2l-y);
	check_equal(y-2, -2+y);
	check_equal(z+y+x, z+x+y);
	check_less(static_compare(math::add_operation_t{}, -y,-x), 0);
	check_equal(inverse(math::add_operation_t{}, (x+y)), -x-y);

	//associativity
	check_equal((x+y)+(x+y), x+y+x+y);
	check_equal((x+y)+(x+y), (x+x)+(y+y));

	//generate powers
	using math::group::power;
	using math::integer;
	check_equal(power(math::add_operation_t{}, integer<2>, x),x+x);
	check_equal(power(math::add_operation_t{}, integer<3>, x),x+power(math::add_operation_t{}, integer<2>, x));
	check_equal(power(math::add_operation_t{}, integer<3>, x),power(math::add_operation_t{}, integer<2>, x)+x);
	check_equal(power(math::add_operation_t{}, integer<5>, x),power(math::add_operation_t{}, integer<2>, x)+power(math::add_operation_t{}, integer<3>, x));
	check_equal(power(math::add_operation_t{}, 5, x),power(math::add_operation_t{}, 2, x)+power(math::add_operation_t{}, 3, x));
	check_equal(power(math::add_operation_t{}, integer<6>, x),x+x+x+x+x+x);
	check_equal(power(math::add_operation_t{}, 2.2, x),x+power(math::add_operation_t{}, 1.2, x));

	//commutation of powers
	check_less(static_compare(math::add_operation_t{}, power(op,integer<2>,y), power(math::add_operation_t{},integer<-1>,power(op,integer<2>,x))), 0);
	check_less(static_compare(math::add_operation_t{}, power(math::add_operation_t{},integer<-1>,power(op,integer<2>,y)), power(op,integer<2>,x)), 0);

	//casts with zero
	using math::zero;
	check_equal(zero+2.4 , 2.4 );
	check_equal(zero+2.4f, 2.4f);
	check_equal(zero+2   , 2   );
	
	return 0;
}

