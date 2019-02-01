#include"scaling.h"
#include"../algebra/unit_test.h"

int main(){
	auto constexpr scaling1=math::geometry::scaling_t{math::ratio<1,4>};
	auto constexpr scaling2=math::geometry::scaling_t{4.2};

	check_equal(scaling1(e0), scaling1.factor*e0);
	check_equal(scaling2(e0), scaling2.factor*e0);
	check_equal(scaling1(2.0*e0), 0.5*e0);

	return 0;
}

