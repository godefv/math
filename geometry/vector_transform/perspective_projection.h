#ifndef GEOMETRY_VECTOR_TRANSFORM_PERSPECTIVE_PROJECTION_H
#define GEOMETRY_VECTOR_TRANSFORM_PERSPECTIVE_PROJECTION_H 

#include"projection.h"
#include"../../eval.h"
#include"../../symbolic/constant.h"

#include<limits>
#include<type_traits>

namespace math::geometry{
	//concept
	template<class T> struct is_perspective_projection:std::false_type{};
	template<class T> concept bool PerspectiveProjection=is_perspective_projection<T>::value;

	//apply
	auto constexpr apply(PerspectiveProjection const& projection, Vector const& operand){
		auto projected_orthographic=projection.orthographic(operand);
		auto depth=norm(operand-projected_orthographic);
		if constexpr(Symbol<decltype(depth)> && Symbol<decltype(projection.min_clip_distance)>){
			if constexpr(eval(depth)<eval(decltype(projection.min_clip_distance){})){
				return projected_orthographic*infinity;
			}else{
				return projected_orthographic/depth;
			}
		}else{
			using ::eval;
			auto depth_runtime=eval(depth);
			if(depth_runtime<eval(projection.min_clip_distance)){
				return projected_orthographic*std::numeric_limits<decltype(inverse(depth_runtime))>::max();
			}else{
				return projected_orthographic/depth_runtime;
			}
		}
	}

	//projection
	template<class SliceT, class DepthT=double>
	struct perspective_projection_t{
		projection_t<SliceT> orthographic;
		DepthT min_clip_distance;
		constexpr perspective_projection_t(SliceT const& s, DepthT const& d)
			:orthographic{projection_t{s}}, min_clip_distance{d} {}
		auto constexpr operator()(auto const& a) const{
			return apply(*this, a);
		}
	};
	template<class SliceT, class DepthT>
	perspective_projection_t(SliceT const&i, DepthT const&)->perspective_projection_t<SliceT,DepthT>;

	template<class SliceT, class DepthT> struct is_perspective_projection<perspective_projection_t<SliceT,DepthT>>:std::true_type{};

	std::ostream& operator<<(std::ostream& out, perspective_projection_t<auto> const& p){
		return out<<"perspective{"<<p.slice<<"}";
	}

	bool constexpr operator==(perspective_projection_t<auto> const& a, perspective_projection_t<auto> const& b){
		return a.slice==b.slice;
	}
	bool constexpr operator!=(perspective_projection_t<auto> const& a, perspective_projection_t<auto> const& b){
		return !(a==b);
	}
}

#endif /* GEOMETRY_VECTOR_TRANSFORM_PERSPECTIVE_PROJECTION_H */
