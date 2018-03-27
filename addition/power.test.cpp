#include"power.h"
#include"../group/unit_test.h"

int main(){
	using math::group::power;
	using math::integer;
	check_equal(power(math::add_operation_t{}, integer<2>,(x+y))
	           ,power(math::add_operation_t{}, integer<2>,x)+power(math::add_operation_t{}, integer<2>,y));
	check_equal(power(math::add_operation_t{}, integer<2>,(x+y+power(math::add_operation_t{}, integer<2>,z)))
	           ,power(math::add_operation_t{}, integer<2>,x)+power(math::add_operation_t{}, integer<2>,y)+power(math::add_operation_t{}, integer<4>, z));
	return 0;
}

