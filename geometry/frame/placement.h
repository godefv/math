#ifndef GEOMETRY_OBJECT_PLACEMENT_H
#define GEOMETRY_OBJECT_PLACEMENT_H 

#include"position.h"
#include"orientation.h"
#include"../point_transform/translation.h"

namespace godefv::math::geometry{
	//pose, placement, or frame
	template<class PositionT, class OrientationT>
	struct placement_t{
		PositionT position;
		OrientationT orientation;
	};
	template<class PositionT, class OrientationT>
	placement_t(PositionT const&, OrientationT const&)->placement_t<PositionT,OrientationT>;

	auto constexpr inverse(placement_t<auto,auto> const& operand){
		auto inverse_orientation=inverse(operand.orientation);
		auto inverse_position=inverse(operand.position);
		return placement_t{
			 position_t{inverse_position.key, change_reference_frame(inverse_position.value, inverse_orientation)}
			,inverse_orientation
		};
	}

	auto constexpr change_reference_frame(Point const& operand, placement_t<auto,auto> const& old_reference){
		return change_reference_frame(change_reference_frame(operand, old_reference.orientation), old_reference.position);
	}

	auto constexpr apply(Translation const& transform, placement_t<auto,auto> const& operand){
		return placement_t{transform(operand.position), operand.orientation};
	}
	auto constexpr apply(point_transform_t<Point,VectorTransform> const& transform, placement_t<auto,auto> const& operand){
		return placement_t{transform(operand.position), transform.vector_transform(operand.orientation)};
	}
}

#endif /* GEOMETRY_OBJECT_PLACEMENT_H */
