#include"vector_transform/perspective_projection.h"
#include"point_transform/from_vector_transform.h"
#include"frame/unit_test.h"
#include"frame/affine_map.h"

#include<vector>

int main(){
	using math::ratio;

	//define the dynamic affine_map of some object
	auto constexpr object_affine_map=math::geometry::affine_map_t{
		 math::geometry::position_t{Po, math::geometry::point(O, 3.0*e1)}
		,math::geometry::linear_map_t{boost::hana::make_map(
			 boost::hana::make_pair(Px, normalized(1.0*e1+1.0*e2))
			,boost::hana::make_pair(Py, normalized(1.0*e1-1.0*e2))
			,boost::hana::make_pair(Pz, 1.0*e3)
		)}
	};
	//simulate loading 3d points from a file
	auto object_points=std::vector<math::geometry::transformed_point_t<decltype(Po.name), math::geometry::translation_t<decltype(1.0*Px+1.0*Py+1.0*Pz)>>>{
		 math::geometry::point(Po, 1.0*Px+0.0*Py+0.0*Pz)
		,math::geometry::point(Po,-1.0*Px+0.0*Py+0.0*Pz)
		,math::geometry::point(Po, 0.0*Px+1.0*Py+0.0*Pz)
		,math::geometry::point(Po, 0.0*Px-1.0*Py+0.0*Pz)
		,math::geometry::point(Po, 0.0*Px+0.0*Py+1.0*Pz)
		,math::geometry::point(Po, 0.0*Px+0.0*Py-1.0*Pz)
	};
	auto object_points_relative_to_world=std::vector<math::geometry::transformed_point_t<decltype(O.name), math::geometry::translation_t<decltype(1.0*e1+1.0*e2+1.0*e3)>>>{object_points.size()};
	std::transform(
		begin(object_points), end(object_points)
		,begin(object_points_relative_to_world)
		,[&](auto const& point){return change_reference_frame(point, object_affine_map);}
	);

	std::cout<<"relative to world"<<std::endl;
	for(auto& point:object_points_relative_to_world){
		std::cout<<point<<std::endl;
	}

	//define the dynamic affine_map of a camera
	auto constexpr camera_affine_map=math::geometry::affine_map_t{
		 math::geometry::position_t{Co, math::geometry::point(object_affine_map.origin_map.value, 2.0*e2)}
		,math::geometry::linear_map_t{boost::hana::make_map(
			 boost::hana::make_pair(Cx, normalized(1.0*e1+1.0*e3)/256)
			,boost::hana::make_pair(Cy, normalized(1.0*e1-1.0*e3)/256)
			,boost::hana::make_pair(Cz, normalized(-2.0*e2))
		)}
	};
	auto world_to_camera=inverse(camera_affine_map);

	auto object_points_relative_to_camera=std::vector<math::geometry::transformed_point_t<decltype(Co.name), math::geometry::translation_t<decltype(1.0*Cx+1.0*Cy+1.0*Cz)>>>{object_points.size()};
	std::transform(
		begin(object_points_relative_to_world), end(object_points_relative_to_world)
		,begin(object_points_relative_to_camera)
		,[&](auto const& point){return change_reference_frame(point, world_to_camera);}
	);

	std::cout<<"relative to camera"<<std::endl;
	for(auto& point:object_points_relative_to_camera){
		std::cout<<point<<std::endl;
	}

	//define camera projection
	auto constexpr camera_projection=make_point_transform(Co, math::geometry::perspective_projection_t{Cz, ratio<1,10>});

	auto object_points_projected=std::vector<math::geometry::transformed_point_t<decltype(Co.name), math::geometry::translation_t<decltype(1.0*Cx+1.0*Cy)>>>{object_points.size()};
	std::transform(
		begin(object_points_relative_to_camera), end(object_points_relative_to_camera)
		,begin(object_points_projected)
		,[&](auto const& point){return camera_projection(point);}
	);

	std::cout<<"image space"<<std::endl;
	for(auto& point:object_points_projected){
		std::cout<<point<<std::endl;
	}

	return 0;
}

