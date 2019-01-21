#include"point_transform.h"
#include"unit_test.h"

//auto constexpr test(auto const&... transforms){
	//auto total_transform=(transforms...)
	//std::cout<<total_transform<<std::endl;
	//check_equal(total_transform(O), )
//}

int main(){
	using math::half_turn;
	using math::ratio;

	auto constexpr translation1=math::geometry::translation_t{e0};
	auto constexpr translation2=math::geometry::translation_t{e0+e1};

	//translation,translation
	check_equal((translation1,translation2), math::geometry::translation_t{math::integer<2>*e0+e1});
	
	auto constexpr homothecy1=math::geometry::make_homothecy(O,ratio<2,3>);
	auto constexpr homothecy2=math::geometry::make_homothecy(A,ratio<1,4>);
	//auto constexpr homothecy3=math::geometry::homothecy_t{4.2};

	//homothecy,translation
	std::cout<<"\n"<<(translation1,homothecy1)<<std::endl;
	check_equal((translation1,homothecy1)(O), homothecy1(translation1(O)));
	check_equal((translation1,homothecy1)(A), homothecy1(translation1(A)));
	check_equal((translation1,homothecy1)(B), homothecy1(translation1(B)));
	check_equal((translation1,homothecy1)(C), homothecy1(translation1(C)));
	check_equal((translation1,homothecy1)(D), homothecy1(translation1(D)));
	std::cout<<"\n"<<(translation1,homothecy2)<<std::endl;
	check_equal((translation1,homothecy2)(O), homothecy2(translation1(O)));
	check_equal((translation1,homothecy2)(A), homothecy2(translation1(A)));
	check_equal((translation1,homothecy2)(B), homothecy2(translation1(B)));
	check_equal((translation1,homothecy2)(C), homothecy2(translation1(C)));
	check_equal((translation1,homothecy2)(D), homothecy2(translation1(D)));

	auto constexpr rotation1=math::geometry::make_point_rotation(O,math::geometry::simple_rotation_t{math::geometry::plane(e1,e2), ratio<1,2>*half_turn});
	//auto constexpr rotation2=math::geometry::simple_rotation_t{math::geometry::plane(e1,n1), ratio<1,2>*half_turn};
	//auto constexpr rotation3=math::geometry::simple_rotation_t{math::geometry::plane(e0,n1), ratio<1,2>*half_turn};
	auto constexpr rotation4=math::geometry::make_point_rotation(A,math::geometry::simple_rotation_t{math::geometry::plane(e0,e1), ratio<3,7>*half_turn});
	//auto constexpr rotation5=math::geometry::simple_rotation_t{math::geometry::plane(e0,e1), 1.2*half_turn};
	
	//rotation,translation
	std::cout<<"\n"<<(translation1,rotation1)<<std::endl;
	check_equal((translation1,rotation1)(O), rotation1(translation1(O)));
	check_equal((translation1,rotation1)(A), rotation1(translation1(A)));
	check_equal((translation1,rotation1)(B), rotation1(translation1(B)));
	check_equal((translation1,rotation1)(C), rotation1(translation1(C)));
	//check_equal((translation1,rotation1)(D), rotation1(translation1(D)));
	std::cout<<"\n"<<(translation1,rotation4)<<std::endl;
	check_equal((translation1,rotation4)(O), rotation4(translation1(O)));
	check_equal((translation1,rotation4)(A), rotation4(translation1(A)));
	check_equal((translation1,rotation4)(B), rotation4(translation1(B)));
	check_equal((translation1,rotation4)(C), rotation4(translation1(C)));
	//check_equal((translation1,rotation4)(D), rotation4(translation1(D)));

	//translation commutation
	std::cout<<"\n"<<(rotation1,translation1,homothecy1)<<std::endl;
	check_equal((rotation1,translation1,homothecy1)(O), homothecy1(translation1(rotation1(O))));
	check_equal((rotation1,translation1,homothecy1)(A), homothecy1(translation1(rotation1(A))));
	check_equal((rotation1,translation1,homothecy1)(B), homothecy1(translation1(rotation1(B))));
	check_equal((rotation1,translation1,homothecy1)(C), homothecy1(translation1(rotation1(C))));
	//check_equal((rotation1,translation1,homothecy1)(D), homothecy1(translation1(rotation1(D))));
	std::cout<<"\n"<<(rotation1,translation1,homothecy1,rotation1)<<std::endl;
	check_equal((rotation1,translation1,homothecy1,rotation1)(O), rotation1(homothecy1(translation1(rotation1(O)))));
	check_equal((rotation1,translation1,homothecy1,rotation1)(A), rotation1(homothecy1(translation1(rotation1(A)))));
	check_equal((rotation1,translation1,homothecy1,rotation1)(B), rotation1(homothecy1(translation1(rotation1(B)))));
	check_equal((rotation1,translation1,homothecy1,rotation1)(C), rotation1(homothecy1(translation1(rotation1(C)))));
	//check_equal((rotation1,translation1,homothecy1,rotation1)(D), rotation1(homothecy1(translation1(rotation1(D)))));

	return 0;
}

