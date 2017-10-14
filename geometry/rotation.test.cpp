#include"rotation.h"
#include"composition.h"
#include"../unit_test.h"

static constexpr auto e0=vector::basis_element_t{group::geometric::direction_positive_t<3>{}, symbolic::integer<1>};
static constexpr auto e1=vector::basis_element_t{group::geometric::direction_positive_t<1>{}, symbolic::integer<1>};
static constexpr auto e2=vector::basis_element_t{group::geometric::direction_positive_t<2>{}, symbolic::integer<1>};
static constexpr auto e3=vector::basis_element_t{group::geometric::direction_negative_t<3>{}, symbolic::integer<1>};

int main(){
	using symbolic::half_turn;

	auto constexpr rotation1=geometry::simple_rotation_t{geometry::plane(e1,e2), symbolic::ratio<1,2>*half_turn};
	auto constexpr rotation2=geometry::simple_rotation_t{geometry::plane(e1,e3), symbolic::ratio<1,2>*half_turn};
	//auto constexpr rotation3=geometry::simple_rotation_t{geometry::plane(e0,e3), symbolic::ratio<1,2>*half_turn};
	auto constexpr R1=rotation1.rotor();
	auto constexpr R2=rotation2.rotor();
	auto constexpr B1=rotation1.bivector();
	auto constexpr half_B1=symbolic::ratio<1,2>*B1;
	using namespace algebra::geometric::operators;
	auto constexpr square_half_B1=half_B1*half_B1;

	using namespace algebra::geometric::operators;

	std::cout<<"cyclic blade "<<rotation1.plane.blade()<<std::endl;
	std::cout<<"angle "<<rotation1.angle<<std::endl;
	std::cout<<"bivector "<<B1<<std::endl;
	std::cout<<"half bivector "<<half_B1<<std::endl;
	std::cout<<"square "<<square_half_B1<<std::endl;
	std::cout<<"scalar "<<square_half_B1.coordinate<<std::endl;
	std::cout<<"scalar abs "<<abs(square_half_B1.coordinate)<<std::endl;
	std::cout<<"sqrt scalar abs "<<sqrt(abs(square_half_B1.coordinate))<<std::endl;
	std::cout<<"normalized half bivector "<<algebra::geometric::normalized(half_B1)<<std::endl;

	std::cout<<"cyclic quaternion("<<e1.element<<","<<e2.element<<"): "<<R1<<std::endl;
	std::cout<<e1+e3<<"->"<<eval(rotation1(e1+e3))<<std::endl;
	std::cout<<e2.element<<"->"<<eval(rotation1(e2))<<std::endl;
	std::cout<<"hyperbolic quaternion("<<e1.element<<","<<e3.element<<"): "<<R2<<std::endl;
	std::cout<<e1.element<<"->"<<rotation2(e1)<<std::endl;
	std::cout<<e3.element<<"->"<<rotation2(e3)<<std::endl;
	unused(rotation1.plane);
	unused(rotation1.angle);

	//auto constexpr rotation12=geometry::compose_operation_t::apply(rotation1, rotation2);
	//std::cout<<rotation12<<std::endl;
	//std::cout<<rotation1.rotor()*rotation2.rotor()-rotation12.rotor()<<std::endl;
	//check_equal(rotation1.rotor()*rotation2.rotor(), rotation12.rotor());
	//check_equal(rotation1(rotation2(e1)), rotation12(e1));
	//check_equal(rotation1(rotation2(e2)), rotation12(e2));
	//check_equal(rotation1(rotation2(e3)), rotation12(e3));

	//auto constexpr rotation13=geometry::compose_operation_t::apply(rotation1, rotation3);
	//std::cout<<rotation13<<std::endl;

	return 0;
}

