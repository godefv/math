#include"power.h"
#include"../symbolic/unit_test.h"

struct dummy_operation_t{
	static auto constexpr apply(auto const& a, auto const& b){
		return a*b;
	}
};
auto constexpr op=dummy_operation_t{};

int main(){
	using namespace math::group;
	using math::integer;
	//special exponents
	check_equal(power(op, integer<0>, x),identity_t<dummy_operation_t>{});
	check_equal(power(op, integer<1>, x),x);
	//power of compile time values
	check_equal(power(op, integer<3>, integer<2>),integer<8>);
	//power of power
	check_equal(power(op, integer<5>, power(op, integer<3>, x)), power(op, integer<15>, x));
	//concept
	check_equal(Power<dummy_operation_t, decltype(power(op, integer<3>, x))>, true);
	check_equal(Power<dummy_operation_t, double>, false);
	return 0;
}
