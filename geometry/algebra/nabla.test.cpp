#include"nabla.h"
#include"wedge_product.h"
#include"unit_test.h"

int main(){
	using math::integer;
	auto constexpr X=k*e1+l*e2+m*e3;
	auto constexpr nabla=math::geometry::nabla_t{X};

	check_equal(nabla*X, integer<3>);
	check_equal(nabla|X, integer<3>);
	check_equal(nabla^X, integer<0>);

	return 0;
}

