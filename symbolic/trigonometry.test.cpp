#include"trigonometry.h"
#include"unit_test.h"

int main(){
	using namespace symbolic;
	check_equal(sin(ratio<0,2>*half_turn), integer<0>);
	check_equal(sin(ratio<1,2>*half_turn), integer<1>);
	check_equal(sin(ratio<2,2>*half_turn), integer<0>);
	check_equal(sin(ratio<3,2>*half_turn), integer<-1>);
	check_equal(sin(ratio<4,2>*half_turn), integer<0>);
	check_equal(sin(ratio<5,2>*half_turn), integer<1>);
	check_equal(sin(ratio<6,2>*half_turn), integer<0>);
	check_equal(sin(ratio<7,2>*half_turn), integer<-1>);
	check_equal(sin(ratio<8,2>*half_turn), integer<0>);

	check_equal(sin(ratio<1,3>*half_turn), vector::basis_element_t{sqrt(integer<3>), ratio<1,2>});
	std::cout<<cos(ratio<1,5>*half_turn)<<std::endl;
	std::cout<<cos(ratio<3,5>*half_turn)<<std::endl;
	std::cout<<sin(ratio<5,12>*half_turn)<<std::endl;
	
	static_assert(Symbol<decltype(ratio<1,4>*half_turn)>);
	static_assert(Symbol<decltype(sinh(ratio<1,4>*half_turn))>);
	static_assert(Symbol<decltype(sinh(x))>);

	check_equal(vector::unit(square(cos(ratio<3,7>*half_turn)))+vector::unit(square(sin(ratio<3,7>*half_turn))), integer<1>);
	check_equal(vector::unit(square(cos(x)))+vector::unit(square(sin(x))), integer<1>);
	check_equal(vector::unit(square(sin(x)))+vector::unit(square(cos(x))), integer<1>);
	check_equal(vector::basis_element_t{square(cos(x)), integer<5>}+vector::basis_element_t{square(sin(x)), integer<5>}, integer<5>);
	//check_equal(vector::scalar_wrapper_t{x}*(vector::unit(square(cos(x)))-vector::unit(square(sin(x)))), x);

	check_equal(vector::unit(square(cosh(x)))-vector::unit(square(sinh(x))), integer<1>);
	check_equal(-vector::unit(square(sinh(x)))+vector::unit(square(cosh(x))), integer<1>);
	check_equal(vector::basis_element_t{square(cosh(x)), integer<5>}-vector::basis_element_t{square(sinh(x)), integer<5>}, integer<5>);
	//check_equal(vector::scalar_wrapper_t{x}*(vector::unit(square(cosh(x)))-vector::unit(square(sinh(x)))), x);

	return 0;
}

