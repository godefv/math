#include"dot_product.h"
#include"../../unit_test.h"

//generators
using e1_t=math::geometry::direction_positive_t<1>;
using e2_t=math::geometry::direction_positive_t<2>;
using e3_t=math::geometry::direction_positive_t<3>;
using n1_t=math::geometry::direction_negative_t<1>;
static constexpr auto e1=e1_t{};
static constexpr auto e2=e2_t{};
static constexpr auto e3=e3_t{};
static constexpr auto n1=n1_t{};

int main(){
	using math::one;
	using math::zero;

	check_equal(e1|e1, one);
	check_equal(e1|e2, zero);
	check_equal(e1|n1, zero);
	check_equal(e1|(e2+e1), one);
	check_equal((e1*e2)|(e1*e2), -one);
	return 0;
}

