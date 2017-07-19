#include"algebra.h"
#include"group/geometric.h"
#include"group/generate.h"

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_positive_t<3>;
using namespace group::geometric;

//mult groups, finite order of generators plus commutation rules guarantees that the group is finite
constexpr auto geometric_group_2d=group::generate(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>), hana_inverse, hana_mult);
constexpr auto complex_group=group::generate(hana::make_set(hana::type_c<mult_t<e1_t,e2_t>>), hana_inverse, hana_mult);
constexpr auto geometric_group_3d=group::generate(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>, hana::type_c<e3_t>), hana_inverse, hana_mult);

template<class ElementT>
using geometric_basis_element_t=algebra::basis_element_t<decltype(geometric_group_3d), one_t, mult_operation_t, inverse_t, double, ElementT>;

using add_operation_t=algebra::add_operation_t<decltype(geometric_group_3d), one_t, mult_operation_t, inverse_t, double>;

template<class A, class B> constexpr auto operator+(A const& a, B const& b){
	return group::apply_operation<add_operation_t>(a,b);
}
//template<class A> constexpr auto operator-(A const& a){
	//return group::inverse_t<add_operation_t, A>{a};
//}
std::ostream& operator<<(std::ostream& out, group::generated_element_t<add_operation_t, auto, auto> const& addition){
	//return algebra::print<decltype(geometric_group_3d), one_t, mult_operation_t, inverse_t, double>(addition);
	return out<<"("<<addition.first<<") + ("<<addition.second<<")";
}

int main(){
	geometric_basis_element_t<e1_t> a{2.};
	geometric_basis_element_t<e2_t> b{3.};
	std::cout<<(a*b)<<std::endl;
	std::cout<<(a+b)<<std::endl;
	std::cout<<(a+b*a)<<std::endl;
	std::cout<<(b*a+a)<<std::endl;
	std::cout<<(a+b*a+a)<<std::endl;
	return 0;
}

