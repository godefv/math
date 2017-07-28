#include"rotation.h"
#include"slice.h"
#include"../algebra/geometric.h"
#include"../group/generate.h"
#include"../algebra/formatting.h"
#include"../vector/formatting.h"
#include"../unit_test.h"

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_positive_t<3>;

//mult groups, finite order of generators plus commutation rules guarantees that the group is finite
namespace hana=boost::hana;
constexpr auto geometric_group_3d=group::generate(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>, hana::type_c<e3_t>), group::geometric::hana_inverse, group::geometric::hana_mult);

using  add_operation_t=algebra::geometric:: add_operation_t<decltype(geometric_group_3d), double>;
using mult_operation_t=algebra::geometric::mult_operation_t<decltype(geometric_group_3d), double>;

template<class A, class B> constexpr auto operator*(A const& a, B const& b){
	return mult_operation_t::apply(a,b);
}
template<class A, class B> constexpr auto operator+(A const& a, B const& b){
	return add_operation_t::apply(a,b);
}
template<class A> constexpr auto operator-(A const& a){
	return add_operation_t::inverse(a);
}
template<class A, class B> constexpr auto operator-(A const& a, B const& b){
	return a+(-b);
}

static constexpr auto e1=1.*e1_t{};
static constexpr auto e2=1.*e2_t{};
static constexpr auto e3=1.*e3_t{};

int main(){
	auto plane12=geometry::plane_t<decltype(e1),decltype(e2)>{e1,e2};
	auto rotation1=geometry::rotation_t<decltype(plane12)>{plane12, M_PI/2};
	//auto rotation2=geometry::rotation_t{geometry::plane_t{rotation1(e1),e3}, pi/2};

	//(rotation2*rotation1)(e1, e2, e3);
	std::cout<<rotation1.quaternion()<<std::endl;
	rotation1.plane;
	rotation1.angle;

	return 0;
}

