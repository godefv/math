#include"power.h"
#include"commutation.h"
#include"unit_test.h"

namespace godefv::math{
auto constexpr cycle_order(dummy_operation_t, z_t){
	return 4;
}
}

int main(){
	using namespace godefv::math::group;
	using math::integer;
	//special exponents
	check_equal(power(op, integer<0>, x),identity_t<dummy_operation_t>{});
	check_equal(power(op, integer<1>, x),x);
	//power of compile time values
	check_equal(power(op, integer<3>, integer<2>),integer<8>);
	//power of power
	check_equal(power(op, integer<5>, power(op, integer<3>, x)), power(op, integer<15>, x));
	//concept
	check_equal(Power<decltype(power(op, integer<3>, x)), dummy_operation_t>, true);
	check_equal(Power<double, dummy_operation_t>, false);
	//cyclic operands
	check_equal(power(op, integer<10>, z), power(op, integer<2>, z));
	check_equal(power(op, integer<-1>, z), power(op, integer<3>, z));
	//commutation
	check_less(static_compare(plus_op, power(op,integer<3>,x), power(op,integer<2>,x)), 0);
	           
	return 0;
}

