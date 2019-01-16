#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H 

#include"../name.h"

namespace math::geometry{
	//Point
	template<class> struct is_point:std::false_type{};
	template<class T> concept bool Point=is_point<T>::value;

	//point
	template<class Name>
	class point_t{
		Name name;
	};
	template<class Name>
	struct is_point<point_t<Name>>:std::true_type{};

	//PointTransform
	template<class F> concept bool PointTransform=requires(F f){
		f(point_t<name_t<'P'>>{});
		//requires Point<decltype(f(point))>;
	};

	//transformed point
	template<class Name, PointTransform PointTransformT>
	struct transformed_point_t{
		point_t<Name> origin;
		PointTransformT transform;
	};
	template<class Name, class PointTransformT>
	struct is_point<transformed_point_t<Name,PointTransformT>>:std::true_type{};

	auto constexpr apply(PointTransform const& transform, point_t<auto> const& point){
		return transformed_point_t{point, transform};
	}
	auto constexpr apply(PointTransform const& transform, transformed_point_t<auto,auto> const& point){
		return transformed_point_t{point.origin, (point.transform,transform)};
	}
}

#endif /* GEOMETRY_POINT_H */
