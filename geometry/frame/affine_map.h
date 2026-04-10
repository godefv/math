#ifndef GODEFV_MATH_GEOMETRY_FRAME_AFFINE_MAP_H
#define GODEFV_MATH_GEOMETRY_FRAME_AFFINE_MAP_H 

#include"position.h"
#include"linear_map.h"

namespace godefv::math::geometry{
	template<class PositionT, class LinearMapT>
	struct affine_map_t{
		PositionT origin_map;
		LinearMapT directions_map;
	};
	template<class PositionT, class LinearMapT>
	affine_map_t(PositionT const&, LinearMapT const&)->affine_map_t<PositionT,LinearMapT>;

	auto constexpr inverse(auto const& operand){
		auto inverse_directions_map=inverse(operand.directions_map);
		auto inverse_origin_map=inverse(operand.origin_map);
		return affine_map_t{
			position_t{inverse_origin_map.key, change_reference_frame(inverse_origin_map.value, inverse_directions_map)}
			,inverse_directions_map
		};
	}

	//operators
	template<class Position1, class LinearMap1, class Position2, class LinearMap2>
	auto constexpr operator==(affine_map_t<Position1,LinearMap1> const& a, affine_map_t<Position2,LinearMap2> const& b){
		return a.origin_map==b.origin_map && a.directions_map==b.directions_map;
	}
	template<class Position1, class LinearMap1, class Position2, class LinearMap2>
	auto constexpr operator!=(affine_map_t<Position1,LinearMap1> const& a, affine_map_t<Position2,LinearMap2> const& b){
		return !(a==b);
	}
	template<class PositionT, class LinearMapT>
	std::ostream& operator<<(std::ostream& out, affine_map_t<PositionT,LinearMapT> const& operand){
		return out<<"affine_map{"<<operand.origin_map<<" ; "<<operand.directions_map<<"}";
	}

	//change_reference_frame
	template<class PositionT, class LinearMapT>
	auto constexpr change_reference_frame(Point auto const& operand, affine_map_t<PositionT,LinearMapT> const& frame_map){
		return change_reference_frame(change_reference_frame(operand, frame_map.directions_map), frame_map.origin_map);
	}
	template<class VectorT, class PositionT, class LinearMapT>
	auto constexpr change_reference_frame(translation_t<VectorT> const& operand, affine_map_t<PositionT,LinearMapT> const& frame_map){
		return translation_t{change_reference_frame(operand.transform, frame_map.directions_map)};
	}
	template<Point CenterT, VectorTransform TransformT, class PositionT, class LinearMapT>
	auto constexpr change_reference_frame(point_transform_t<CenterT,TransformT> const& operand, affine_map_t<PositionT,LinearMapT> const& frame_map){
		return make_point_transform(
			 change_reference_frame(operand.center, frame_map.origin_map)
			,change_reference_frame(operand.vector_transform, frame_map.directions_map)
		);
	}
	auto constexpr change_reference_frame_endomorphism=group::endomorphism(compose_operation_t{}, [](auto const& a, auto const & ref){return change_reference_frame(a, ref);});
	template<class PositionT, class LinearMapT>
	auto constexpr change_reference_frame(group::Generated<compose_operation_t> auto const& operand, affine_map_t<PositionT,LinearMapT> const& frame_map){
		return change_reference_frame_endomorphism(operand, frame_map);
	}

	//apply geometric tranformations
	template<class PositionT, class LinearMapT>
	auto constexpr apply(Translation auto const& transform, affine_map_t<PositionT,LinearMapT> const& operand){
		return affine_map_t{transform(operand.origin_map), operand.directions_map};
	}
	template<Point CenterT, VectorTransform TransformT, class PositionT, class LinearMapT>
	auto constexpr apply(point_transform_t<CenterT,TransformT> const& transform, affine_map_t<PositionT,LinearMapT> const& operand){
		return affine_map_t{transform(operand.origin_map), transform.vector_transform(operand.directions_map)};
	}

}

#endif /* GODEFV_MATH_GEOMETRY_FRAME_AFFINE_MAP_H */
