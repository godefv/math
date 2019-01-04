#include"composition.h"
#include"algebra/unit_test.h"

int main(){
	using math::half_turn;
	using math::ratio;

	auto constexpr rotation1=math::geometry::simple_rotation_t{math::geometry::plane(e1,e2), ratio<1,2>*half_turn};
	//auto constexpr rotation2=math::geometry::simple_rotation_t{math::geometry::plane(e1,n1), ratio<1,2>*half_turn};
	//auto constexpr rotation3=math::geometry::simple_rotation_t{math::geometry::plane(e0,n1), ratio<1,2>*half_turn};
	auto constexpr rotation4=math::geometry::simple_rotation_t{math::geometry::plane(e0,e1), ratio<3,7>*half_turn};
	//auto constexpr rotation5=math::geometry::simple_rotation_t{math::geometry::plane(e0,e1), 1.2*half_turn};

	auto constexpr rotation14=(rotation1,rotation4);
	auto constexpr rotation14_inverse=inverse(rotation14);
	std::cout<<rotation14<<std::endl;
	std::cout<<rotation14_inverse<<std::endl;
	check_equal((rotation14_inverse,rotation14), geometry::identity);
	////using group::geometric::x;
	////check_equal(rotation4(rotation1(x)), (rotation1,rotation4)(x));
	//check_equal(rotation4(rotation1(e0)), (rotation1,rotation4)(e0));
	//check_equal(rotation4(rotation1(e1)), (rotation1,rotation4)(e1));

	return 0;
}

