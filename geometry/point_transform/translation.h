#ifndef GEOMETRY_TRANSLATION_H
#define GEOMETRY_TRANSLATION_H 

#include"../object/point.h"
#include"../algebra/grade.h"
#include"../../composition/operation.h"

namespace godefv::math::geometry{
	template<Vector VectorT>
	struct translation_t{
		VectorT vector;
		auto constexpr operator()(auto const& operand) const{
			return apply(*this, operand);
		}
	};

	template<Vector VectorT>
	translation_t(VectorT const&)->translation_t<VectorT>;

	template<class VectorT> struct is_point_transform<translation_t<VectorT>>:std::true_type{};

	template<PointTransform PointTransform1, PointTransform PointTransform2> 
	struct is_point_transform<generated_by_composition_t<PointTransform1,PointTransform2>>:std::true_type{};


	template<class VectorT>
	std::ostream& operator<<(std::ostream& out, translation_t<VectorT> const& t){
		return out<<"translation{"<<t.vector<<"}";
	}

	template<class Vector1, class Vector2>
	bool constexpr operator==(translation_t<Vector1> const& a, translation_t<Vector2> const& b){
		return a.vector==b.vector;
	}
	template<class Vector1, class Vector2>
	bool constexpr operator!=(translation_t<Vector1> const& a, translation_t<Vector2> const& b){
		return !(a==b);
	}
	//std::strong_equality operator<=>(translation_t const&, translation_t const&) = default;

	//concept
	template<class> struct is_translation:std::false_type{};
	template<Vector VectorT>
	struct is_translation<translation_t<VectorT>>:std::true_type{};
	template<class T> concept Translation=is_translation<T>::value;

	//inverse
	template<class VectorT>
	auto constexpr inverse(translation_t<VectorT> const& operand){
		return translation_t{-operand.vector};
	}

	//composition of point transformations - translations
	auto constexpr operator,(Translation auto const& a, Translation auto const& b){
		return translation_t{a.vector+b.vector};
	}

	//apply
	template<class VectorT, class Name>
	auto constexpr apply(translation_t<VectorT> const& transform, point_t<Name> const& point){
		return transformed_point_t{point, transform};
	}
	template<class VectorT, class Name, class PointTransformT>
	auto constexpr apply(translation_t<VectorT> const& transform, transformed_point_t<Name,PointTransformT> const& point){
		return transformed_point_t{point.origin, (point.transform,transform)};
	}

	//point
	auto constexpr point(Point auto const& origin, Vector auto const& vector){
		return translation_t{vector}(origin);
	}
	auto constexpr point(Vector auto const& vector){
		return translation_t{vector}(default_origin);
	}
}

#endif /* GEOMETRY_TRANSLATION_H */
