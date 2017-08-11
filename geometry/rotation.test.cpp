#include"rotation.h"
#include"composition.h"
#include"../unit_test.h"

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_negative_t<3>;

using namespace algebra::geometric::operators;

static constexpr auto one=1.*group::geometric::one;
static constexpr auto e1=1.*e1_t{};
static constexpr auto e2=1.*e2_t{};
static constexpr auto e3=1.*e3_t{};

int main(){
	auto constexpr rotation1=geometry::simple_rotation_t{geometry::plane(e1,e2), M_PI/2};
	auto constexpr rotation2=geometry::simple_rotation_t{geometry::plane(e1,e3), M_PI/2};
	auto constexpr q=rotation1.quaternion();

	std::cout<<"cyclic quaternion("<<e1.element()<<","<<e2.element()<<"): "<<rotation1.quaternion()<<std::endl;
	std::cout<<e1+e3<<"->"<<rotation1(e1+e3)<<std::endl;
	std::cout<<e2.element()<<"->"<<rotation1(e2)<<std::endl;
	std::cout<<"hyperbolic quaternion("<<e1.element()<<","<<e3.element()<<"): "<<rotation2.quaternion()<<std::endl;
	std::cout<<e1.element()<<"->"<<rotation2(e1)<<std::endl;
	std::cout<<e3.element()<<"->"<<rotation2(e3)<<std::endl;
	unused(rotation1.plane);
	unused(rotation1.angle);

	//auto constexpr rotation12=geometry::compose_operation_t::apply(rotation1, rotation2);

	return 0;
}

