#ifndef GEOMETRY_POINT_TRANSFORM_H
#define GEOMETRY_POINT_TRANSFORM_H 

#include"translation.h"
#include"../object/point.h"
#include"../vector_transform/composition.h"

namespace godefv::math::geometry{
	template<Point CenterT, VectorTransform TransformT>
	struct point_transform_t{
		CenterT center;
		TransformT vector_transform;
		auto constexpr operator()(auto const& operand) const{
			return apply(*this, operand);
		}
	};
	template<class Name, VectorTransform TransformT>
	point_transform_t(point_t<Name> const&, TransformT const&)->point_transform_t<point_t<Name>, TransformT>;

	template<class CenterT, class TransformT> 
	struct is_point_transform<point_transform_t<CenterT,TransformT>>:std::true_type{};

	template<class Name>
	auto constexpr make_point_transform(point_t<Name> const& center, VectorTransform auto const& transform){
		return point_transform_t{center,transform};
	}
	template<class Name, class PointTransformT>
	auto constexpr make_point_transform(transformed_point_t<Name,PointTransformT> const& center, VectorTransform auto const& transform){
		return inverse(center.transform),make_point_transform(center.origin, transform),center.transform;
	}

	template<Point CenterT, class ScalarT>
	using homothecy_t=point_transform_t<CenterT,scaling_t<ScalarT>>;
	inline auto constexpr make_homothecy(Point auto const& center, auto const& ratio){
		return make_point_transform(center, scaling_t{ratio});
	}
	template<class Direction1, class Direction2>
	inline auto constexpr make_point_rotation(Point auto const& center, plane_t<Direction1,Direction2> const& plane, auto const& angle){
		return make_point_transform(center, simple_rotation_t{plane,angle});
	}

	//operators
	template<class Center1, class Transform1, class Center2, class Transform2>
	bool constexpr operator==(point_transform_t<Center1,Transform1> const& a, point_transform_t<Center2,Transform2> const& b){
		return a.center==b.center && a.vector_transform==b.vector_transform;
	}
	template<class Center1, class Transform1, class Center2, class Transform2>
	bool constexpr operator!=(point_transform_t<Center1,Transform1> const& a, point_transform_t<Center2,Transform2> const& b){
		return !(a==b);
	}
	template<class CenterT, class TransformT>
	std::ostream& operator<<(std::ostream& out, point_transform_t<CenterT,TransformT> const& operand){
		return out<<"point_transform{from "<<operand.center.name<<","<<operand.vector_transform<<"}";
	}

	//apply
	template<class Name, class TransformT>
	auto constexpr apply(point_transform_t<point_t<Name>, TransformT> const&, point_t<Name> const& operand){
		return operand;
	}
	template<class Name, class TransformT, class VectorT>
	auto constexpr apply(point_transform_t<point_t<Name>, TransformT> const& transform, transformed_point_t<Name,translation_t<VectorT>> const& operand){
		return transformed_point_t{operand.origin, translation_t{transform.vector_transform(operand.transform.vector)}};
	}

	//composition of point transformations - point_transform_t with the same center
	template<Point CenterT, class Transform1, class Transform2>
   	auto constexpr operator,(point_transform_t<CenterT,Transform1> const& a, point_transform_t<CenterT,Transform2> const& b){
		return point_transform_t{CenterT{}, (a.vector_transform,b.vector_transform)};
	}
	//composition of point transformations - put scalings first and translations last
	template<class CenterT, class TransformT>
   	auto constexpr operator,(Translation auto const& a, point_transform_t<CenterT,TransformT> const& b){
   		return (b,translation_t{b.vector_transform(a.vector)});
   	}
	
}

#endif /* GEOMETRY_POINT_TRANSFORM_H */
