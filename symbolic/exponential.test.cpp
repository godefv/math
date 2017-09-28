#include"exponential.h"
#include"../unit_test.h"
#include<cmath>

auto test(symbolic::Ratio a, double epsilon){
	auto constexpr exp_a=exp(a);
	print_type(exp_a);
	check_less(std::abs(exp_a-std::exp(a)), epsilon);
}

int main(){
	test(symbolic::ratio<8,10>, 1e-8);
	test(symbolic::ratio<9,10>, 1e-7);
	test(symbolic::ratio<13,14>, 1e-7);
	//test(symbolic::ratio<23,25>, 1e-4);
	//test(symbolic::ratio<99,100>, 1e-4);
	return 0;
}

