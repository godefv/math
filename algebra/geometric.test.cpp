#include"geometric.h"
#include"exponential.h"
#include"reverse.h"
#include"formatting.h"
#include"../group/generate.h"
#include"../vector/formatting.h"
#include"../unit_test.h"

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_positive_t<3>;

//mult groups, finite order of generators plus commutation rules guarantees that the group is finite
namespace hana=boost::hana;
constexpr auto geometric_group_3d=group::generate(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>, hana::type_c<e3_t>), group::geometric::hana_inverse, group::geometric::hana_mult);

template<class ElementT> requires algebra::BasisElementsTemplateParameters<decltype(geometric_group_3d), group::geometric::one_t, group::geometric::mult_operation_t, group::geometric::inverse_t, double, ElementT>
using geometric_basis_element_t=vector::basis_element_t<ElementT, double>;

using  add_operation_t=algebra::geometric:: add_operation_t<decltype(geometric_group_3d), double>;
using mult_operation_t=algebra::geometric::mult_operation_t<decltype(geometric_group_3d), double>;

constexpr auto operator*(auto const& a, auto const& b){
	return mult_operation_t::apply(a,b);
}
constexpr auto operator+(auto const& a, auto const& b){
	return add_operation_t::apply(a,b);
}
constexpr auto operator-(auto const& a){
	return add_operation_t::inverse(a);
}
constexpr auto operator-(auto const& a, auto const& b){
	return a+(-b);
}

static constexpr auto one=1.*group::geometric::one_t{};
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
	check_equal(a*b, geometric_basis_element_t<group::geometric::mult_t<e1_t,e2_t>>{a.coordinate*b.coordinate});
	//commutation
	static_assert(Sorted<decltype(geometric_group_3d),e1_t,e2_t>);
	check_equal(a+b, group::generated_element_t<add_operation_t, decltype(a), decltype(b)>{a,b});
	check_equal(b+a, a+b);
	check_equal(a+b+a, 2.*a+b);
	check_equal(b+a+b, a+2.*b);
	check_equal(a+b+a-b, 2.*a+0.*b);
	check_equal((a+b)*a, a*a+b*a);
	check_equal(a*(a+b), a*a+a*b);
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

