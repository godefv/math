#ifndef GEOMETRY_OBJECT_POSITION_H
#define GEOMETRY_OBJECT_POSITION_H 

#include"../object/point.h"
#include"../point_transform/from_vector_transform.h"

namespace godefv::math::geometry{
	template<class Name, Point PointT>
	struct position_t{
		point_t<Name> key;
		PointT value;
	};
	template<class Name, Point PointT>
	position_t(point_t<Name> const&, PointT const&)->position_t<Name,PointT>;

	//operators
	auto constexpr operator==(position_t<auto,auto> const& a, position_t<auto,auto> const& b){
		return a.key==b.key && a.value==b.value;
	}
	auto constexpr operator!=(position_t<auto,auto> const& a, position_t<auto,auto> const& b){
		return !(a==b);
	}
	std::ostream& operator<<(std::ostream& out, position_t<auto,auto> const& operand){
		return out<<"position{"<<operand.key<<":="<<operand.value<<"}";
	}

	//
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

	auto constexpr apply(PointTransform const& transform, position_t<auto,auto> const& operand){
		return position_t{operand.key, transform(operand.value)};
	}
	template<class Name>
	auto constexpr apply(point_transform_t<point_t<Name>,VectorTransform> const&, position_t<Name,auto> const& operand){
		return operand;
	}
}

#endif /* GEOMETRY_OBJECT_POSITION_H */
