#include"operation.h"
#include"../symbolic/unit_test.h"

struct dummy_operation_t{
	static auto constexpr apply(auto const& a, auto const& b){
		return a*b;
	}
};
auto constexpr op=dummy_operation_t{};

auto constexpr operator*(auto const& a, auto const& b){
	return math::group::operation<dummy_operation_t>(a,b);
}

int main(){
	//associativity
	check_equal(x*(y*z), (x*y)*z);

	//operations with inverse
	using math::group::inverse;
	using math::group::identity_t;
	check_equal(inverse(op, x)*x,identity_t<dummy_operation_t>{});
	check_equal(inverse(op, x*y),inverse(op, y)*inverse(op, x));

	//operations with identity
	check_equal(x, x*identity_t<dummy_operation_t>{});
	check_equal(x*identity_t<dummy_operation_t>{}, x);

	//generate powers
	using math::group::power;
	using math::integer;
	check_equal(power(op, integer<2>, x),x*x);
	check_equal(power(op, integer<3>, x),x*power(op, integer<2>, x));
	check_equal(power(op, integer<3>, x),power(op, integer<2>, x)*x);
	check_equal(power(op, integer<5>, x),power(op, integer<2>, x)*power(op, integer<3>, x));
	check_equal(power(op, integer<6>, x),x*x*x*x*x*x);

	//other
	unused((x*y)*(y*x));

	return 0;
}

