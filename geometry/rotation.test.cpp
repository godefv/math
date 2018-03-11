#include"rotation.h"
#include"composition.h"
#include"../unit_test.h"

static constexpr auto e0=vector::unit_t<group::geometric::direction_positive_t<3>>{};
static constexpr auto e1=vector::unit_t<group::geometric::direction_positive_t<1>>{};
static constexpr auto e2=vector::unit_t<group::geometric::direction_positive_t<2>>{};
static constexpr auto e3=vector::unit_t<group::geometric::direction_negative_t<3>>{};

auto test_bivector(geometry::simple_rotation_t<auto,auto,auto> const& rotation){
	auto B=rotation.bivector();

	std::cout<<"grade of bivector(): ";
	check_equal(algebra::geometric::grades(B), algebra::geometric::grades<2>());

	using namespace boost::hana::literals;
	using namespace algebra::geometric::operators;

	check_equal(B^rotation.plane.directions[0_c], algebra::geometric::zero);
	check_equal(B^rotation.plane.directions[1_c], algebra::geometric::zero);
	check_equal(algebra::geometric::grades(B|(rotation.plane.directions[1_c]^rotation.plane.directions[0_c])), algebra::geometric::grades<0>());
	std::cout<<std::endl;
}

auto test_rotor(geometry::simple_rotation_t<auto,auto,auto> const& rotation){
	auto B=rotation.bivector();
	//auto R=rotation.rotor();

	auto constexpr half_B=symbolic::ratio<1,2>*B;
	using namespace algebra::geometric::operators;
	auto constexpr square_half_B=half_B*half_B;

	std::cout<<"cyclic blade "<<rotation.plane.blade()<<std::endl;
	std::cout<<"angle "<<rotation.angle<<std::endl;
	std::cout<<"bivector "<<B<<std::endl;
	std::cout<<"half bivector "<<half_B<<std::endl;
	std::cout<<"square "<<square_half_B<<std::endl;
	std::cout<<"scalar "<<square_half_B.coordinate<<std::endl;
	std::cout<<"scalar abs "<<abs(square_half_B.coordinate)<<std::endl;
	std::cout<<"sqrt scalar abs "<<sqrt(abs(square_half_B.coordinate))<<std::endl;
	std::cout<<"normalized half bivector "<<algebra::geometric::normalized(half_B)<<std::endl;
	std::cout<<std::endl;
}

auto test_rotation(geometry::simple_rotation_t<auto,auto,auto> const& rotation){
	using namespace boost::hana::literals;
	using namespace algebra::geometric::operators;
	static constexpr auto I=e0^e1^e2^e3;
	auto plane=(rotation.plane.directions[1_c]^rotation.plane.directions[0_c]);
	auto ortho=plane|I;
	check_equal(rotation(plane), plane);
	check_equal(rotation(ortho), ortho);
}

int main(){
	using symbolic::half_turn;

	auto constexpr rotation1=geometry::simple_rotation_t{geometry::plane(e1,e2), symbolic::ratio<1,2>*half_turn};
	auto constexpr rotation2=geometry::simple_rotation_t{geometry::plane(e1,e3), symbolic::ratio<1,2>*half_turn};
	auto constexpr rotation3=geometry::simple_rotation_t{geometry::plane(e0,e3), symbolic::ratio<1,2>*half_turn};

	test_bivector(rotation1);
	test_bivector(rotation2);
	test_bivector(rotation3);

	//test_rotor(rotation1);
	//test_rotor(rotation2);
	//test_rotor(rotation3);

	test_rotation(rotation1);
	test_rotation(rotation2);
	test_rotation(rotation3);

	auto constexpr R1=rotation1.rotor();
	auto constexpr R2=rotation2.rotor();
	using namespace algebra::geometric::operators;

	std::cout<<"cyclic quaternion("<<e1.element<<","<<e2.element<<"): "<<R1<<std::endl;
	std::cout<<e1+e3     <<"->"; check_equal(rotation1(e1+e3), e3-e2); 
	std::cout<<e2.element<<"->"; check_equal(rotation1(e2   ), e1   ); 
	std::cout<<"hyperbolic quaternion("<<e1.element<<","<<e3.element<<"): "<<R2<<std::endl;
	//check_equal(rotation2(e1), );
	std::cout<<e1.element<<"->"<<rotation2(e1)<<" = "<<eval(rotation2(e1))<<std::endl;
	std::cout<<e3.element<<"->"<<rotation2(e3)<<" = "<<eval(rotation2(e3))<<std::endl;
	unused(rotation1.plane);
	unused(rotation1.angle);

	//auto constexpr rotation12=geometry::compose_operation_t::apply(rotation1, rotation2);
	auto constexpr rotation12=R1*R2;
	std::cout<<rotation12<<std::endl;
	//std::cout<<rotation1.rotor()*rotation2.rotor()-rotation12.rotor()<<std::endl;
	//check_equal(rotation1.rotor()*rotation2.rotor(), rotation12.rotor());
	//check_equal(rotation1(rotation2(e1)), rotation12(e1));
	//check_equal(rotation1(rotation2(e2)), rotation12(e2));
	//check_equal(rotation1(rotation2(e3)), rotation12(e3));

	//auto constexpr rotation13=geometry::compose_operation_t::apply(rotation1, rotation3);
	//std::cout<<rotation13<<std::endl;

	return 0;
}

