#ifndef GEOMETRY_VECTOR_TRANSFORM_PROJECTION_H
#define GEOMETRY_VECTOR_TRANSFORM_PROJECTION_H 

#include"../object/slice.h"
#include"../algebra/dot_product.h"

namespace math::geometry{
	//concept
	template<class T> struct is_orthographic_projection:std::false_type{};
	template<class T> concept bool OrthographicProjection=is_orthographic_projection<T>::value;

	//apply
	auto constexpr apply(OrthographicProjection const& projection, Vector const& operand){
		auto blade=projection.slice.blade();
		return project(inverse(blade)*(blade|operand), grades(operand));
	}

	//projection
	template<class SliceT>
	struct projection_t{
		SliceT slice;
		auto constexpr operator()(auto const& a) const{
			return apply(*this, a);
		}
	};
	template<class SliceT>
	projection_t(SliceT const&)->projection_t<SliceT>;

	template<class SliceT> struct is_orthographic_projection<projection_t<SliceT>>:std::true_type{};

	std::ostream& operator<<(std::ostream& out, projection_t<auto> const& p){
		return out<<"projection{"<<p.slice<<"}";
	}

	bool constexpr operator==(projection_t<auto> const& a, projection_t<auto> const& b){
		return a.slice==b.slice;
	}
	bool constexpr operator!=(projection_t<auto> const& a, projection_t<auto> const& b){
		return !(a==b);
	}
}

#endif /* GEOMETRY_VECTOR_TRANSFORM_PROJECTION_H */
