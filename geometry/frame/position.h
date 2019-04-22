#ifndef GEOMETRY_OBJECT_POSITION_H
#define GEOMETRY_OBJECT_POSITION_H 

#include"../object/point.h"

namespace godefv::math::geometry{
	template<class Name, Point PointT>
	struct position_t{
		point_t<Name> key;
		PointT value;
	};
	template<class Name, Point PointT>
	position_t(point_t<Name> const&, PointT const&)->position_t<Name,PointT>;

	auto constexpr inverse(position_t<auto,transformed_point_t<auto,auto>> const& operand){
		return position_t{operand.value.origin, transformed_point_t{operand.key, inverse(operand.value.transform)}};
	}

	template<Symbol Name>
	auto constexpr change_reference_frame(transformed_point_t<Name,auto> const& operand, position_t<Name,point_t<Name>> const& old_reference){
		return operand;
	}
	template<Symbol Name>
	auto constexpr change_reference_frame(point_t<Name>, position_t<Name,auto> const& old_reference){
		return old_reference.value;
	}
	template<Symbol Name>
	auto constexpr change_reference_frame(transformed_point_t<Name,auto> const& operand, position_t<Name,transformed_point_t<auto,auto>> const& old_reference){
		return transformed_point_t{old_reference.value.origin, (old_reference.value.transform,operand.transform)};
	}
}

#endif /* GEOMETRY_OBJECT_POSITION_H */
