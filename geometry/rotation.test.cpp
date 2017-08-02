#include"rotation.h"
#include"slice.h"
#include"../algebra/geometric.h"
#include"../vector/formatting.h"
#include"../unit_test.h"

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_negative_t<3>;

using  add_operation_t=algebra::geometric:: add_operation_t<double>;
using mult_operation_t=algebra::geometric::mult_operation_t<double>;

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

static constexpr auto one=1.*group::geometric::one_t{};
static constexpr auto e1=1.*e1_t{};
static constexpr auto e2=1.*e2_t{};
static constexpr auto e3=1.*e3_t{};

int main(){
	auto rotation1=geometry::rotation(geometry::plane(e1,e2), M_PI/2);
	auto rotation2=geometry::rotation(geometry::plane(e1,e3), M_PI/2);

	std::cout<<"cyclic quaternion("<<e1.element()<<","<<e2.element()<<"): "<<rotation1.quaternion()<<std::endl;
	std::cout<<e1.element()<<"->"<<rotation1(e1)<<std::endl;
	std::cout<<e2.element()<<"->"<<rotation1(e2)<<std::endl;
	std::cout<<"hyperbolic quaternion("<<e1.element()<<","<<e3.element()<<"): "<<rotation2.quaternion()<<std::endl;
	std::cout<<e1.element()<<"->"<<rotation2(e1)<<std::endl;
	std::cout<<e3.element()<<"->"<<rotation2(e3)<<std::endl;
	rotation1.plane;
	rotation1.angle;

	return 0;
}

