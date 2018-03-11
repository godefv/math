#include"addition.h"
#include"../unit_test.h"

#include<cstdlib>

template<class A, class B> constexpr auto operator+(A const& a, B const& b){
	return vector::add_operation_t::apply(a,b);
}
template<class A> constexpr auto operator-(A const& a){
	return vector::add_operation_t::inverse(a);
}
template<class A, class B> constexpr auto operator-(A const& a, B const& b){
	return a+(-b);
}

static constexpr auto e1=vector::basis_element_t{group::indexed_element_t<1>{}, 1.};
static constexpr auto e2=vector::basis_element_t{group::indexed_element_t<2>{}, 1.};
static constexpr auto e3=vector::basis_element_t{group::indexed_element_t<3>{}, 1.};

auto check_vector(vector::Vector){}

int main(){
	check_vector(e1);
	check_vector(e1+e2);
	check_vector(e1-e2);
	check_vector(2.*e1);
	check_vector(2.*e1-4.5*e3);
	//colinear
	check_equal(e1+2.*e1, 3.*e1);
	check_equal(-e1, -1.*e1);
	check_equal(2.*e1-e1, 1.*e1);
	check_equal(e1-e1, 0.*e1);
	//commutation
	check_equal(e2+e1, e1+e2);
	check_equal(e1+e2+e1, 2.*e1+e2);
	check_equal(e2+e1+e2, e1+2.*e2);
	check_equal(e1+e2+e1-e2, 2.*e1+0.*e2);


	return 0;
}

