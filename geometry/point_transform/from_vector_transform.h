#ifndef GEOMETRY_POINT_TRANSFORM_H
#define GEOMETRY_POINT_TRANSFORM_H 

#include"translation.h"
#include"../object/point.h"
#include"../vector_transform/composition.h"

namespace math::geometry{
	template<Point CenterT, VectorTransform TransformT>
	struct point_transform_t{
		CenterT center;
		TransformT vector_transform;
		auto constexpr operator()(Point const& a) const{
			return apply(*this, a);
		}
	};
	template<class Name, VectorTransform TransformT>
	point_transform_t(point_t<Name> const&, TransformT const&)->point_transform_t<point_t<Name>, TransformT>;

	auto constexpr make_point_transform(point_t<auto> const& center, VectorTransform const& transform){
		return point_transform_t{center,transform};
	}
	auto constexpr make_point_transform(transformed_point_t<auto,auto> const& center, VectorTransform const& transform){
		return inverse(center.transform),make_point_transform(center.origin, transform),center.transform;
	}

	template<Point CenterT, class ScalarT>
	using homothecy_t=point_transform_t<CenterT,scaling_t<ScalarT>>;
	inline auto constexpr make_homothecy(Point const& center, auto const& ratio){
		return make_point_transform(center, scaling_t{ratio});
	}
	inline auto constexpr make_point_rotation(Point const& center, plane_t<auto,auto> const& plane, auto const& angle){
		return make_point_transform(center, simple_rotation_t{plane,angle});
	}

	//operators
	bool constexpr operator==(point_transform_t<auto,auto> const& a, point_transform_t<auto,auto> const& b){
		return a.center==b.center && a.vector_transform==b.vector_transform;
	}
	bool constexpr operator!=(point_transform_t<auto,auto> const& a, point_transform_t<auto,auto> const& b){
		return !(a==b);
	}
	std::ostream& operator<<(std::ostream& out, point_transform_t<auto,auto> const& operand){
		return out<<"point_transform{from "<<operand.center.name<<","<<operand.vector_transform<<"}";
	}

	//apply
	template<class Name>
	auto constexpr apply(point_transform_t<point_t<Name>, auto> const&, point_t<Name> const& operand){
		return operand;
	}
	template<class Name>
	auto constexpr apply(point_transform_t<point_t<Name>, auto> const& transform, transformed_point_t<Name,translation_t<auto>> const& operand){
		return transformed_point_t{operand.origin, translation_t{transform.vector_transform(operand.transform.vector)}};
	}

	//composition of point transformations - point_transform_t with the same center
	template<Point CenterT>
   	auto constexpr operator,(point_transform_t<CenterT,auto> const& a, point_transform_t<CenterT,auto> const& b){
		return point_transform_t{CenterT{}, (a.vector_transform,b.vector_transform)};
	}
	//composition of point transformations - put scalings first and translations last
   	auto constexpr operator,(Translation const& a, point_transform_t<auto,auto> const& b){
   		return (b,translation_t{b.vector_transform(a.vector)});
   	}
	
}

#endif /* GEOMETRY_POINT_TRANSFORM_H */
