#include"geometric.h"
#include"exponential.h"
#include"reverse.h"
#include"../unit_test.h"

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_positive_t<3>;
using n1_t=group::geometric::direction_negative_t<1>;

static constexpr auto zero=group::identity_t<algebra::geometric::add_operation_t>{};
static constexpr auto one=vector::basis_element_t{group::geometric::one, 1.};
static constexpr auto e1=vector::basis_element_t{e1_t{}, 1.};
static constexpr auto e2=vector::basis_element_t{e2_t{}, 1.};
static constexpr auto e3=vector::basis_element_t{e3_t{}, 1.};
static constexpr auto n1=vector::basis_element_t{n1_t{}, 1.};

int main(){
	using namespace algebra::geometric::operators;
	using math::pi;

	auto a=2.*e1;
	auto b=3.*e2;
	auto c=5.*e3;

	//colinear
	check_equal(a+a, 2.*a);
	check_equal(-a, -1.*a);
	check_equal(a-a, 0.*a);
	//product of basis elements
	check_equal(a*b, vector::basis_element_t{group::geometric::mult_t<e1_t,e2_t>{}, a.coordinate*b.coordinate});
	//commutation
	static_assert(static_compare(e1,e2)>0);
	check_equal(a+b, group::generated_element_t{algebra::geometric::add_operation_t{},a,b});
	check_equal(b+a, a+b);
	check_equal(a+b+a, 2.*a+b);
	check_equal(b+a+b, a+2.*b);
	check_equal(a+b+a-b, 2.*a+0.*b);
	check_equal((a+b)*a, a*a+b*a);
	check_equal(a*(a+b), a*a+a*b);
	static_assert(static_compare(e1*e3,e1*e2)<0);
	check_equal((a+b)*(c+b), a*c+a*b+b*c+b*b);
	check_equal((a+b)*(a+b), a*a+a*b+b*a+b*b);
	//reverse
	check_equal(reverse(e1*e2), e2*e1);
	check_equal(reverse(one+e1*e2), one+e2*e1);
	//grades
	namespace hana=boost::hana;
	using namespace hana::literals;
	static_assert(algebra::geometric::grades(one)            == hana::make_set(0_c));
	static_assert(algebra::geometric::grades(e1)             == hana::make_set(1_c));
	static_assert(algebra::geometric::grades(e1*e2)          == hana::make_set(2_c));
	static_assert(algebra::geometric::grades(e1*e2+e1*e3)    == hana::make_set(2_c));
	static_assert(algebra::geometric::grades(e1*e2*e3)       == hana::make_set(3_c));
	static_assert(algebra::geometric::grades(one+e2+e1*e2*e3)== hana::make_set(0_c,1_c,3_c));
	//project
	check_equal(algebra::geometric::project(one+e1, hana::make_set(1_c)), e1);
	check_equal(algebra::geometric::project(one+e1, hana::make_set(0_c)), one);
	check_equal(algebra::geometric::project(one+e1+e1*e2, hana::make_set(0_c,2_c)), one+e1*e2);
	check_equal(algebra::geometric::project(one+e1+e1*e2, hana::make_set(0_c,3_c)), one);
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
 
	std::cout<<"symetry   : "<<-(e3*(3.*e3+e1+2.*e2)*e3)<<std::endl;
	std::cout<<"rotation  : "<<0.5*((e1+e3)*e3*(3.*e3+e1+2.*e2)*e3*(e1+e3))<<std::endl;
	std::cout<<"projected : "<<algebra::geometric::project(0.5*((e1+e3)*e3*(3.*e3+e1+2.*e2)*e3*(e1+e3)), hana::make_set(1_c))<<std::endl;
	std::cout<<"quaternion: "<<algebra::exp(pi/4*e1*e2)<<std::endl;
	std::cout<<"reversed  : "<<reverse(algebra::exp(pi/4*e1*e2))<<std::endl;

	return 0;
}

