#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H 

#include"../../symbolic/symbol.h"
#include"../../symbolic/name.h"

namespace math::geometry{
	//Point
	template<class> struct is_point:std::false_type{};
	template<class T> concept bool Point=is_point<T>::value;

	//point
	template<class Name>
	class point_t{
		Name name;
	};
	template<class Name> point_t(Name const&)->point_t<Name>;
	template<class Name> struct is_point<point_t<Name>>:std::true_type{};

	//default origin
	using default_origin_t=math::geometry::point_t<math::name_t<'O'>>; 
	default_origin_t default_origin;

	//operators
	bool constexpr operator==(point_t<auto> const& a, point_t<auto> const& b){
		return a.name==b.name;
	}
	bool constexpr operator!=(point_t<auto> const& a, point_t<auto> const& b){
		return !(a==b);
	}
	std::ostream& operator<<(std::ostream& out, point_t<auto> const& operand){
		return out<<operand.name;
	}

	//PointTransform
	template<class F> concept bool PointTransform=requires(F f){
		requires Point<decltype(f(point_t<name_t<'P'>>{}))>;
	};

	//transformed point
	template<class Name, class PointTransformT>
	struct transformed_point_t{
		point_t<Name> origin;
		PointTransformT transform;
	};
	template<class Name, class PointTransformT>
	transformed_point_t(point_t<Name> const&, PointTransformT const&)->transformed_point_t<Name,PointTransformT>;
	template<class Name, class PointTransformT>
	struct is_point<transformed_point_t<Name,PointTransformT>>:std::true_type{};

	//operators
	bool constexpr operator==(transformed_point_t<auto,auto> const& a, transformed_point_t<auto,auto> const& b){
		return a.origin==b.origin && a.transform==b.transform;
	}
	bool constexpr operator!=(transformed_point_t<auto,auto> const& a, transformed_point_t<auto,auto> const& b){
		return !(a==b);
	}
	std::ostream& operator<<(std::ostream& out, transformed_point_t<auto,auto> const& operand){
		return out<<"point{"<<operand.origin.name<<","<<operand.transform<<"}";
	}
}
namespace math{
	template<Symbol Name> struct is_symbol<geometry::point_t<Name>>: std::true_type{};
}

#endif /* GEOMETRY_POINT_H */
