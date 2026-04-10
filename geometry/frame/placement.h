#ifndef GEOMETRY_OBJECT_PLACEMENT_H
#define GEOMETRY_OBJECT_PLACEMENT_H 

#include"position.h"
#include"orientation.h"
#include"affine_map.h"
#include"../point_transform/translation.h"
#include"../point_transform/from_vector_transform.h"

namespace godefv::math::geometry{
	//pose, placement, or frame
	template<class PositionT, class OrientationT>
	struct placement_t{
		PositionT position;
		OrientationT orientation;
	};
	template<class PositionT, class OrientationT>
	placement_t(PositionT const&, OrientationT const&)->placement_t<PositionT,OrientationT>;

	//operators
	template<class Position1, class Orientation1, class Position2, class Orientation2>
	auto constexpr operator==(placement_t<Position1,Orientation1> const& a, placement_t<Position2,Orientation2> const& b){
		return a.position==b.position && a.orientation==b.orientation;
	}
	template<class Position1, class Orientation1, class Position2, class Orientation2>
	auto constexpr operator!=(placement_t<Position1,Orientation1> const& a, placement_t<Position2,Orientation2> const& b){
		return !(a==b);
	}
	template<class PositionT, class OrientationT>
	std::ostream& operator<<(std::ostream& out, placement_t<PositionT,OrientationT> const& operand){
		return out<<"placement{"<<operand.position<<" ; "<<operand.orientation<<"}";
	}

	//apply geometric tranformations
	template<class PositionT, class OrientationT>
	auto constexpr apply(Translation auto const& transform, placement_t<PositionT,OrientationT> const& operand){
		return placement_t{transform(operand.position), operand.orientation};
	}
	template<Point CenterT, VectorTransform TransformT, class PositionT, class OrientationT>
	auto constexpr apply(point_transform_t<CenterT,TransformT> const& transform, placement_t<PositionT,OrientationT> const& operand){
		return placement_t{transform(operand.position), transform.vector_transform(operand.orientation)};
	}

	//inverse
	template<class PositionT, class OrientationT>
	auto constexpr inverse(placement_t<PositionT,OrientationT> const& operand){
		auto inverse_orientation=inverse(operand.orientation);
		auto inverse_position=inverse(operand.position);
		return placement_t{
			 position_t{inverse_position.key, change_reference_frame(inverse_position.value, to_linear_map(inverse_orientation))}
			,inverse_orientation
		};
	}

	//to_affine_map
	template<class PositionT, class OrientationT>
	auto constexpr to_affine_map(placement_t<PositionT,OrientationT> const& operand){
		return affine_map_t{operand.position, to_linear_map(operand.orientation)};
	}

	//change_reference_frame
	//use `change_reference_frame(operand, to_affine_map(placement))`
	
}

#endif /* GEOMETRY_OBJECT_PLACEMENT_H */
