#include"rotation.h"
#include"algebra/unit_test.h"

auto test_bivector(math::geometry::simple_rotation_t<auto,auto,auto> const& rotation){
	auto B=rotation.bivector();

	std::cout<<"grade of bivector(): ";
	check_equal(math::geometry::grades(B), math::geometry::grades<2>());

	using namespace boost::hana::literals;

	check_equal(B^rotation.plane.directions[0_c], math::zero);
	check_equal(B^rotation.plane.directions[1_c], math::zero);
	check_equal(math::geometry::grades(B|(rotation.plane.directions[1_c]^rotation.plane.directions[0_c])), math::geometry::grades<0>());
	std::cout<<std::endl;
}

auto test_rotor(math::geometry::simple_rotation_t<auto,auto,auto> const& rotation){
	auto B=rotation.bivector();
	//auto R=rotation.rotor();

	auto constexpr half_B=math::ratio<1,2>*B;
	auto constexpr square_half_B=half_B*half_B;

	std::cout<<"cyclic blade "<<rotation.plane.blade()<<std::endl;
	std::cout<<"angle "<<rotation.angle<<std::endl;
	std::cout<<"bivector "<<B<<std::endl;
	std::cout<<"half bivector "<<half_B<<std::endl;
	std::cout<<"square "<<square_half_B<<std::endl;
	std::cout<<"scalar abs "<<abs(square_half_B)<<std::endl;
	std::cout<<"sqrt scalar abs "<<sqrt(abs(square_half_B))<<std::endl;
	std::cout<<"normalized half bivector "<<math::geometry::normalized(half_B)<<std::endl;
	std::cout<<std::endl;
}

auto test_rotation(math::geometry::simple_rotation_t<auto,auto,auto> const& rotation){
	using namespace boost::hana::literals;
	static constexpr auto I=e0^e1^e2^n1;
	auto plane=(rotation.plane.directions[1_c]^rotation.plane.directions[0_c]);
	auto ortho=plane|I;
	std::cout<<"rotation plane is invariant: ";
	check_equal(rotation(plane), plane);
	std::cout<<"dual of rotation plane is invariant: ";
	check_equal(rotation(ortho), ortho);
	std::cout<<std::endl;
}

int main(){
	using math::half_turn;
	using math::ratio;

	auto constexpr rotation1=math::geometry::simple_rotation_t{math::geometry::plane(e1,e2), ratio<1,2>*half_turn};
	auto constexpr rotation2=math::geometry::simple_rotation_t{math::geometry::plane(e1,n1), ratio<1,2>*half_turn};
	auto constexpr rotation3=math::geometry::simple_rotation_t{math::geometry::plane(e0,n1), ratio<1,2>*half_turn};
	auto constexpr rotation4=math::geometry::simple_rotation_t{math::geometry::plane(e0,e1), ratio<3,7>*half_turn};

	test_bivector(rotation1);
	test_bivector(rotation2);
	test_bivector(rotation3);
	test_bivector(rotation4);

	test_rotor(rotation1);
	test_rotor(rotation2);
	test_rotor(rotation3);

	test_rotation(rotation1);
	test_rotation(rotation2);
	test_rotation(rotation3);
	test_rotation(rotation4);

	std::cout<<e1+n1<<"->"; check_equal(rotation1(e1+n1), n1-e2); 
	std::cout<<e2   <<"->"; check_equal(rotation1(e2   ), e1   ); 
	std::cout<<e1   <<"->"<<rotation2(e1)<<" = "<<eval(rotation2(e1))<<std::endl;
	std::cout<<n1   <<"->"<<rotation2(n1)<<" = "<<eval(rotation2(n1))<<std::endl;

	//auto constexpr rotation14=(rotation1,rotation4);
	//auto constexpr rotation14_inverse=geometry::compose_operation_t::inverse(rotation14);
	//std::cout<<rotation14<<std::endl;
	//std::cout<<rotation14_inverse<<std::endl;
	//check_equal((rotation14_inverse,rotation14), geometry::identity);
	////using group::geometric::x;
	////check_equal(rotation4(rotation1(vector::unit(x))), (rotation1,rotation4)(vector::unit(x)));
	//check_equal(rotation4(rotation1(e0)), (rotation1,rotation4)(e0));
	//check_equal(rotation4(rotation1(e1)), (rotation1,rotation4)(e1));

	return 0;
}

