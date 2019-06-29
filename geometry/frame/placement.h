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
	auto constexpr operator==(placement_t<auto,auto> const& a, placement_t<auto,auto> const& b){
		return a.position==b.position && a.orientation==b.orientation;
	}
	auto constexpr operator!=(placement_t<auto,auto> const& a, placement_t<auto,auto> const& b){
		return !(a==b);
	}
	std::ostream& operator<<(std::ostream& out, placement_t<auto,auto> const& operand){
		return out<<"placement{"<<operand.position<<" ; "<<operand.orientation<<"}";
	}

	//apply geometric tranformations
	auto constexpr apply(Translation const& transform, placement_t<auto,auto> const& operand){
		return placement_t{transform(operand.position), operand.orientation};
	}
	auto constexpr apply(point_transform_t<Point,VectorTransform> const& transform, placement_t<auto,auto> const& operand){
		return placement_t{transform(operand.position), transform.vector_transform(operand.orientation)};
	}

	//inverse
	auto constexpr inverse(placement_t<auto,auto> const& operand){
		auto inverse_orientation=inverse(operand.orientation);
		auto inverse_position=inverse(operand.position);
		return placement_t{
			 position_t{inverse_position.key, change_reference_frame(inverse_position.value, to_linear_map(inverse_orientation))}
			,inverse_orientation
		};
	}

	//to_affine_map
	auto constexpr to_affine_map(placement_t<auto,auto> const& operand){
		return affine_map_t{operand.position, to_linear_map(operand.orientation)};
	}

	//change_reference_frame
	//use `change_reference_frame(operand, to_affine_map(placement))`
	
}

#endif /* GEOMETRY_OBJECT_PLACEMENT_H */
