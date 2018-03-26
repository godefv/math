#include"geometric.h"
#include"exponential.h"
#include"reverse.h"
#include"../unit_test.h"

#include<boost/hana.hpp>

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_positive_t<3>;
using n1_t=group::geometric::direction_negative_t<1>;

using vector::zero;
static constexpr auto one=vector::unit_t<group::geometric::one_t>{};
static constexpr auto e1=vector::unit_t<e1_t>{};
static constexpr auto e2=vector::unit_t<e2_t>{};
static constexpr auto e3=vector::unit_t<e3_t>{};
static constexpr auto n1=vector::unit_t<n1_t>{};

int main(){
	using namespace algebra::geometric::operators;
	using symbolic::half_turn;

	auto a=symbolic::integer<2>*e1;
	auto b=symbolic::integer<3>*e2;
	auto c=symbolic::integer<5>*e3;

	//colinear
	check_equal(a+a, symbolic::integer<2>*a);
	check_equal(-a, symbolic::integer<-1>*a);
	check_equal(a-a, vector::zero);
	//product of basis elements
	check_equal(a*b, vector::basis_vector_t{group::geometric::mult_t<e1_t,e2_t>{}, a.coordinate*b.coordinate});
	check_equal(a*a, vector::basis_vector_t{group::geometric::one_t{}, a.coordinate*a.coordinate});
	//commutation
	static_assert(static_compare(e1,e2)>0);
	check_equal(a+b, group::generated_by_operation_t{algebra::geometric::add_operation_t{},a,b});
	check_equal(b+a, a+b);
	check_equal(a+b+a, symbolic::integer<2>*a+b);
	check_equal(b+a+b, a+symbolic::integer<2>*b);
	check_equal(a+b+a-b, symbolic::integer<2>*a);
	check_equal((a+b)*a, a*a+b*a);
	check_equal(a*(a+b), a*a+a*b);
	static_assert(static_compare(e1*e3,e1*e2)<0);
	check_equal((a+b)*(c+b), a*c+a*b+b*c+b*b);
	check_equal((a+b)*(a+b), a*a+a*b+b*a+b*b);
	//reverse
	check_equal(reverse(e1*e2), e2*e1);
	check_equal(reverse(one+e1*e2), one+e2*e1);
	//wedge
	{auto constexpr e1e2=algebra::geometric::group_wedge_operation_t::apply(e1_t{}, e2_t{}); unused(e1e2);}
	{auto constexpr e1e2=e1^e2; unused(e1e2);}
	check_equal(e1^e1, zero);
	check_equal(e1^e2, e1*e2);
	check_equal(e1^n1, e1*n1);
	check_equal(e1^(e2+e1), e1*e2);
	//dot
	{auto constexpr e1e2=algebra::geometric::group_dot_operation_t::apply(e1_t{}, e2_t{}); unused(e1e2);}
	{auto constexpr e1e2=e1|e2; unused(e1e2);}
	check_equal(e1|e1, one);
	check_equal(e1|e2, zero);
	check_equal(e1|n1, zero);
	check_equal(e1|(e2+e1), one);
	check_equal((e1^e2)|(e1^e2), -one);
 
	auto sqrt_5_element=symbolic::nth_root<2>(symbolic::integer<5>);
	auto sqrt_5=vector::unit(sqrt_5_element);
	auto sqrt_5_e1=vector::scalar_wrapper_t{sqrt_5}*e1;
	check_equal(sqrt_5_e1*sqrt_5_e1, vector::basis_vector_t{one.element, symbolic::integer<5>});
	
	std::cout<<"symetry   : "<<-(e3*(3.*e3+e1+2.*e2)*e3)<<std::endl;
	std::cout<<"rotation  : "<<0.5*((e1+e3)*e3*(symbolic::integer<3>*e3+e1+symbolic::integer<2>*e2)*e3*(e1+e3))<<std::endl;
	std::cout<<"projected : "<<algebra::geometric::project(0.5*((e1+e3)*e3*(3.*e3+e1+2.*e2)*e3*(e1+e3)), grades<1>())<<std::endl;
	auto constexpr bivector=vector::scalar_wrapper_t{half_turn*symbolic::ratio<1,4>}*(e1*e2);
	std::cout<<"quaternion: "<<algebra::exp<group::geometric::one_t>(bivector)<<std::endl;
	std::cout<<"quaternion: "<<algebra::geometric::exp(bivector)<<std::endl;
	std::cout<<"reversed  : "<<reverse(algebra::exp<group::geometric::one_t>(bivector))<<std::endl;
	std::cout<<"reversed  : "<<reverse(algebra::geometric::exp(bivector))<<std::endl;

	return 0;
}

