#include"composition.h"
#include"algebra/unit_test.h"

int main(){
	//identity
	check_equal(math::geometry::identity(e0), e0);
	check_equal(math::geometry::identity(e1), e1);
	check_equal(math::geometry::identity(n1), n1);

	return 0;
}

