#include"rotation.h"
#include"composition.h"
#include"../unit_test.h"

static constexpr auto e0=vector::basis_element_t{group::geometric::direction_positive_t<3>{}, 1.};
static constexpr auto e1=vector::basis_element_t{group::geometric::direction_positive_t<1>{}, 1.};
static constexpr auto e2=vector::basis_element_t{group::geometric::direction_positive_t<2>{}, 1.};
static constexpr auto e3=vector::basis_element_t{group::geometric::direction_negative_t<3>{}, 1.};

int main(){
	using math::pi;
	using namespace algebra::geometric::operators;

	auto constexpr rotation1=geometry::simple_rotation_t{geometry::plane(e1,e2), pi/2};
	auto constexpr rotation2=geometry::simple_rotation_t{geometry::plane(e1,e3), pi/2};
	auto constexpr rotation3=geometry::simple_rotation_t{geometry::plane(e0,e3), pi/2};
	{auto constexpr q=rotation1.rotor();unused(q);}

	std::cout<<"cyclic quaternion("<<e1.element<<","<<e2.element<<"): "<<rotation1.rotor()<<std::endl;
	std::cout<<e1+e3<<"->"<<rotation1(e1+e3)<<std::endl;
	std::cout<<e2.element<<"->"<<rotation1(e2)<<std::endl;
	std::cout<<"hyperbolic quaternion("<<e1.element<<","<<e3.element<<"): "<<rotation2.rotor()<<std::endl;
	std::cout<<e1.element<<"->"<<rotation2(e1)<<std::endl;
	std::cout<<e3.element<<"->"<<rotation2(e3)<<std::endl;
	unused(rotation1.plane);
	unused(rotation1.angle);

	auto constexpr rotation12=geometry::compose_operation_t::apply(rotation1, rotation2);
	std::cout<<rotation12<<std::endl;
	std::cout<<rotation1.rotor()*rotation2.rotor()-rotation12.rotor()<<std::endl;
	//check_equal(rotation1.rotor()*rotation2.rotor(), rotation12.rotor());
	//check_equal(rotation1(rotation2(e1)), rotation12(e1));
	//check_equal(rotation1(rotation2(e2)), rotation12(e2));
	//check_equal(rotation1(rotation2(e3)), rotation12(e3));

	auto constexpr rotation13=geometry::compose_operation_t::apply(rotation1, rotation3);
	std::cout<<rotation13<<std::endl;

	return 0;
}

