#include"from_vector_transform.h"
#include"unit_test.h"
#include"../../eval.h"
#include"../../cpp20_array.h"
#include"../export/coordinates.h"

#include<fstream>

//auto constexpr test(auto const&... transforms){
	//auto total_transform=(transforms...)
	//std::cout<<total_transform<<std::endl;
	//check_equal(total_transform(O), )
//}

// for angles, the library needs to know the sign of their square
namespace godefv::math{
	auto constexpr eval_with_data(group::generated_power_t<mult_operation_t,integer_t<2>,k_t>, decltype(boost::hana::nothing)){return 1;}
	auto constexpr eval_with_data(group::generated_power_t<mult_operation_t,integer_t<2>,l_t>, decltype(boost::hana::nothing)){return 1;}
}

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
	std::cout<<"\n"<<(translation1,homothecy2)<<std::endl;
	check_equal((translation1,homothecy2)(O), homothecy2(translation1(O)));
	check_equal((translation1,homothecy2)(A), homothecy2(translation1(A)));
	check_equal((translation1,homothecy2)(B), homothecy2(translation1(B)));
	check_equal((translation1,homothecy2)(C), homothecy2(translation1(C)));
	check_equal((translation1,homothecy2)(D), homothecy2(translation1(D)));

	auto constexpr rotation1=math::geometry::make_point_rotation(O, math::geometry::plane(e1,e2), ratio<1,2>*half_turn);
	//auto constexpr rotation2=math::geometry::simple_rotation_t{math::geometry::plane(e1,n1), ratio<1,2>*half_turn};
	//auto constexpr rotation3=math::geometry::simple_rotation_t{math::geometry::plane(e0,n1), ratio<1,2>*half_turn};
	auto constexpr rotation4=math::geometry::make_point_rotation(A, math::geometry::plane(e0,e1), ratio<3,7>*half_turn);
	//auto constexpr rotation5=math::geometry::simple_rotation_t{math::geometry::plane(e0,e1), 1.2*half_turn};
	
	//rotation,translation
	std::cout<<"\n"<<(translation1,rotation1)<<std::endl;
	check_equal((translation1,rotation1)(O), rotation1(translation1(O)));
	check_equal((translation1,rotation1)(A), rotation1(translation1(A)));
	check_equal((translation1,rotation1)(B), rotation1(translation1(B)));
	check_equal((translation1,rotation1)(C), rotation1(translation1(C)));
	check_equal((translation1,rotation1)(D), rotation1(translation1(D)));
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
	std::cout<<"\n"<<(rotation1,translation1,homothecy2,rotation1)<<std::endl;
	check_equal((rotation1,translation1,homothecy2,rotation1)(O), rotation1(homothecy2(translation1(rotation1(O)))));
	check_equal((rotation1,translation1,homothecy2,rotation1)(A), rotation1(homothecy2(translation1(rotation1(A)))));
	check_equal((rotation1,translation1,homothecy2,rotation1)(B), rotation1(homothecy2(translation1(rotation1(B)))));
	check_equal((rotation1,translation1,homothecy2,rotation1)(C), rotation1(homothecy2(translation1(rotation1(C)))));
	check_equal((rotation1,translation1,homothecy2,rotation1)(D), rotation1(homothecy2(translation1(rotation1(D)))));

	//make a 3D torus
	auto constexpr translation_r=math::geometry::translation_t{m*e0};
	auto constexpr translation_R=math::geometry::translation_t{n*e0};
	auto constexpr rotation_c=math::geometry::make_point_rotation(O, math::geometry::plane(e0,e2), k*half_turn);
	auto constexpr rotation_C=math::geometry::make_point_rotation(O, math::geometry::plane(e0,e1), l*half_turn);
	auto constexpr torus_equation=(translation_r,rotation_c,translation_R,rotation_C)(O);
	auto constexpr torus_normals_equation=(rotation_c.vector_transform,rotation_C.vector_transform)(e0);
	std::cout<<"torus equation : "<<torus_equation<<std::endl;
	std::vector<decltype(1.0*e0+1.0*e1+1.0*e2)> torus_points;
	std::vector<decltype(1.0*e0+1.0*e1+1.0*e2)> torus_normals;
	auto step_k=0.1;
	auto step_l=0.05;
    for(auto i=0; i*step_k<2.0; ++i)
    for(auto j=0; j*step_l<2.0; ++j){
		//at each step draw a quad
		for(auto [di,dj]:std20::to_array<std::pair<int,int>>({{0,0},{0,1},{1,1},{1,0}})){
			auto evaluate_parameters=[&](auto symbol){
				     if(symbol==m){return 1.0;}
				else if(symbol==n){return 5.0;}
				else if(symbol==k){return (i+di)*step_k;}
				else if(symbol==l){return (j+dj)*step_l;}
				return 10000.0;
			};
			torus_points.push_back(eval_with_data(torus_equation.transform.vector, evaluate_parameters));
			torus_normals.push_back(eval_with_data(torus_normals_equation, evaluate_parameters)); 
		}
	}
	// export to x3d file
	std::ofstream torus_file{"/tmp/godefv_math_torus.x3d"};
	torus_file<<"<x3d width='500px' height='500px'><scene>"<<std::endl;
	torus_file<<"<viewpoint position='0 0 30'></viewpoint>"<<std::endl;
	torus_file<<"<shape><appearance><material></material></appearance><QuadSet>"<<std::endl;
	torus_file<<"<Coordinate point='";
	math::geometry::print_coordinates(torus_file, torus_points, boost::hana::make_tuple(e0,e1,e2));
	torus_file<<"'/>\n";
	torus_file<<"<Normal vector='";
	math::geometry::print_coordinates(torus_file, torus_normals, boost::hana::make_tuple(e0,e1,e2));
	torus_file<<"'/>\n";
	torus_file<<"</QuadSet></shape>"<<std::endl;
	torus_file<<"</scene></x3d>"<<std::endl;

	return 0;
}

