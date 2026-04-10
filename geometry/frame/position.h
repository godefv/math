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
	template<class Name1, class Point1, class Name2, class Point2>
	auto constexpr operator==(position_t<Name1,Point1> const& a, position_t<Name2,Point2> const& b){
		return a.key==b.key && a.value==b.value;
	}
	template<class Name1, class Point1, class Name2, class Point2>
	auto constexpr operator!=(position_t<Name1,Point1> const& a, position_t<Name2,Point2> const& b){
		return !(a==b);
	}
	template<class Name, class PointT>
	std::ostream& operator<<(std::ostream& out, position_t<Name,PointT> const& operand){
		return out<<"position{"<<operand.key<<":="<<operand.value<<"}";
	}

	//
	template<class Name1, class Name2, class PointTransformT>
	auto constexpr inverse(position_t<Name1,transformed_point_t<Name2,PointTransformT>> const& operand){
		return position_t{operand.value.origin, transformed_point_t{operand.key, inverse(operand.value.transform)}};
	}

	template<Symbol Name, class PointTransformT>
	auto constexpr change_reference_frame(transformed_point_t<Name,PointTransformT> const& operand, position_t<Name,point_t<Name>> const& old_reference){
		return operand;
	}
	template<Symbol Name, class PointT>
	auto constexpr change_reference_frame(point_t<Name>, position_t<Name,PointT> const& old_reference){
		return old_reference.value;
	}
	template<Symbol Name, class PointTransformT, class Name2, class PointTransform2>
	auto constexpr change_reference_frame(transformed_point_t<Name,PointTransformT> const& operand, position_t<Name,transformed_point_t<Name2,PointTransform2>> const& old_reference){
		return transformed_point_t{old_reference.value.origin, (old_reference.value.transform,operand.transform)};
	}

	template<class Name, class PointT>
	auto constexpr apply(PointTransform auto const& transform, position_t<Name,PointT> const& operand){
		return position_t{operand.key, transform(operand.value)};
	}
	template<class Name, VectorTransform TransformT, class PointT>
	auto constexpr apply(point_transform_t<point_t<Name>,TransformT> const&, position_t<Name,PointT> const& operand){
		return operand;
	}
}

#endif /* GEOMETRY_OBJECT_POSITION_H */
