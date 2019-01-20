#ifndef GEOMETRY_TRANSLATION_H
#define GEOMETRY_TRANSLATION_H 

#include"point.h"
#include"composition.h"

namespace math::geometry{
	template<Vector VectorT>
	struct translation_t{
		VectorT vector;
		auto constexpr operator()(Point const& point) const{
			return apply(*this, point);
		}
	};

	template<Vector VectorT>
	translation_t(VectorT const&)->translation_t<VectorT>;

	std::ostream& operator<<(std::ostream& out, translation_t<auto> const& t){
		return out<<"translation{"<<t.vector<<"}";
	}

	bool constexpr operator==(translation_t<auto> const& a, translation_t<auto> const& b){
		return a.vector==b.vector;
	}
	bool constexpr operator!=(translation_t<auto> const& a, translation_t<auto> const& b){
		return !(a==b);
	}
	//std::strong_equality operator<=>(translation_t const&, translation_t const&) = default;

	//concept
	template<class> struct is_translation:std::false_type{};
	template<Vector VectorT>
	struct is_translation<translation_t<VectorT>>:std::true_type{};
	template<class T> concept bool Translation=is_translation<T>::value;

	//inverse
	auto constexpr inverse(translation_t<auto> const& operand){
		return translation_t{-operand.vector};
	}

	//composition of point transformations - translations
	Translation{Translation2}
	auto constexpr operator,(Translation const& a, Translation2 const& b){
		return translation_t{a.vector+b.vector};
	}

	//apply
	auto constexpr apply(translation_t<auto> const& transform, point_t<auto> const& point){
		return transformed_point_t{point, transform};
	}
	auto constexpr apply(translation_t<auto> const& transform, transformed_point_t<auto,auto> const& point){
		return transformed_point_t{point.origin, (point.transform,transform)};
	}

	//make_point
	auto constexpr make_point(point_t<auto> const& origin, Vector const& vector){
		return translation_t{vector}(origin);
	}
	auto constexpr make_point(Vector const& vector){
		return translation_t{vector}(default_origin);
	}
}

#endif /* GEOMETRY_TRANSLATION_H */
