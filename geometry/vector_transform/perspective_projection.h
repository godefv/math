#ifndef GEOMETRY_VECTOR_TRANSFORM_PERSPECTIVE_PROJECTION_H
#define GEOMETRY_VECTOR_TRANSFORM_PERSPECTIVE_PROJECTION_H 

#include"projection.h"
#include"../../eval.h"
#include"../../symbolic/constant.h"

#include<limits>
#include<type_traits>

namespace godefv::math::geometry{
	//concept
	template<class T> struct is_perspective_projection:std::false_type{};
	template<class T> concept PerspectiveProjection=is_perspective_projection<T>::value;

	//apply
	auto constexpr apply(PerspectiveProjection const& projection, Vector const& operand){
		auto depth=operand|inverse(projection.direction);
		//auto projected_orthographic=operand-depth*projection.direction;
		auto projected_orthographic=project((operand^inverse(projection.direction))*projection.direction, grades(operand));
		if constexpr(Symbol<decltype(depth)> && Symbol<decltype(projection.min_clip_distance)>){
			if constexpr(eval(depth)<eval(decltype(projection.min_clip_distance){})){
				return projected_orthographic*infinity;
			}else{
				return projected_orthographic/depth;
			}
		}else{
			using godefv::math::eval;
			auto depth_runtime=eval(depth);
			if(depth_runtime<eval(projection.min_clip_distance)){
				using math::inverse;
				return projected_orthographic*std::numeric_limits<decltype(inverse(depth_runtime))>::max();
			}else{
				return projected_orthographic/depth_runtime;
			}
		}
	}

	//projection
	template<Vector Direction, class ClipDistanceT>
	struct perspective_projection_t{
		Direction direction;
		ClipDistanceT min_clip_distance;
		auto constexpr operator()(auto const& a) const{
			return apply(*this, a);
		}
	};
	template<Vector Direction, class ClipDistanceT>
	perspective_projection_t(Direction const&, ClipDistanceT const&)->perspective_projection_t<Direction, ClipDistanceT>;

	template<class SliceT, class DepthT> struct is_perspective_projection<perspective_projection_t<SliceT,DepthT>>:std::true_type{};

	std::ostream& operator<<(std::ostream& out, perspective_projection_t<auto,auto> const& p){
		return out<<"perspective{"<<p.slice<<"}";
	}

	bool constexpr operator==(perspective_projection_t<auto,auto> const& a, perspective_projection_t<auto,auto> const& b){
		return a.slice==b.slice;
	}
	bool constexpr operator!=(perspective_projection_t<auto,auto> const& a, perspective_projection_t<auto,auto> const& b){
		return !(a==b);
	}
}

#endif /* GEOMETRY_VECTOR_TRANSFORM_PERSPECTIVE_PROJECTION_H */
