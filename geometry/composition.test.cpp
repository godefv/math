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
	
	auto constexpr translation1=math::geometry::translation_t{e0};
	auto constexpr translation2=math::geometry::translation_t{e0+e1};

	auto constexpr scaling1=math::geometry::scaling_t{ratio<2,3>};
	auto constexpr scaling2=math::geometry::scaling_t{ratio<1,4>};
	//auto constexpr scaling3=math::geometry::scaling_t{4.2};

	//identity
	check_equal(math::geometry::identity(e0), e0);
	check_equal(math::geometry::identity(e1), e1);
	check_equal(math::geometry::identity(n1), n1);

	//rotation,rotation
	auto constexpr rotation14=(rotation1,rotation4);
	auto constexpr rotation14_inverse=inverse(rotation14);
	check_equal((rotation14_inverse,rotation14), math::geometry::identity);
	check_equal(rotation4(rotation1(e0)), rotation14(e0));
	check_equal(rotation4(rotation1(e1)), rotation14(e1));
	check_equal(rotation4(rotation1(n1)), rotation14(n1));
	//check_equal(rotation4(rotation1(x)), (rotation1,rotation4)(x));

	//translation,translation
	check_equal((translation1,translation2), math::geometry::translation_t{math::integer<2>*e0+e1});
	
	//scaling,scaling
	check_equal((scaling1,scaling2), math::geometry::scaling_t{ratio<1,6>});

	//homotheciy,rotation
	check_equal((rotation1,scaling1), (scaling1,rotation1));

	//scaling,translation
	check_equal((translation1,scaling1), (scaling1,math::geometry::translation_t{scaling1(translation1.vector)}));

	//rotation,translation
	check_equal((translation1,rotation1), (rotation1,math::geometry::translation_t{rotation1(translation1.vector)}));

	//translation,translation commutation
	check_equal((rotation1,translation1,scaling1), (scaling1,rotation1,math::geometry::translation_t{rotation1(scaling1(translation1.vector))}));
	check_equal((rotation1,translation1,scaling1,rotation1), (scaling1,(rotation1,rotation1),math::geometry::translation_t{rotation1(scaling1(translation1.vector))}));
	//check_equal((rotation1,translation1,scaling1,rotation1)(e1), rotation1(scaling1(translation1(rotation1(e1)))));

	return 0;
}

