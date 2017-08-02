#include"geometric.h"
#include"exponential.h"
#include"reverse.h"
#include"../vector/formatting.h"
#include"../unit_test.h"

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_positive_t<3>;

using namespace algebra::geometric::operators;

static constexpr auto one=1.*group::geometric::one;
static constexpr auto e1=1.*e1_t{};
static constexpr auto e2=1.*e2_t{};
static constexpr auto e3=1.*e3_t{};

int main(){
	auto a=2.*e1;
	auto b=3.*e2;
	auto c=5.*e3;
	auto xy=e1*e2;

	//colinear
	check_equal(a+a, 2.*a);
	check_equal(-a, -1.*a);
	check_equal(a-a, 0.*a);
	//product of basis elements
	check_equal(a*b, vector::basis_element_t<group::geometric::mult_t<e1_t,e2_t>, double>{a.coordinate*b.coordinate});
	//commutation
	static_assert(static_compare(e1,e2)>0);
	check_equal(a+b, group::generated_element_t{algebra::geometric::add_operation_t<double>{},a,b});
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

	std::cout<<"symetry   : "<<-(e3*(3.*e3+e1+2.*e2)*e3)<<std::endl;
	std::cout<<"rotation  : "<<0.5*((e1+e3)*e3*(3.*e3+e1+2.*e2)*e3*(e1+e3))<<std::endl;
	std::cout<<"quaternion: "<<algebra::exp(M_PI/4*e1*e2)<<std::endl;
	std::cout<<"reverse   : "<<reverse(algebra::exp(M_PI/4*e1*e2))<<std::endl;

	return 0;
}

