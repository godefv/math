#ifndef GEOMETRY_TRANSFORM_H
#define GEOMETRY_TRANSFORM_H 

#include"rotation.h"
#include"scaling.h"
#include"translation.h"

namespace math::geometry{
	template<class T> concept bool VectorTransform=Scaling<T> || Rotation<T>;

	auto constexpr apply(VectorTransform const& transform, translation_t<auto> const& operand){
		return translation_t{apply(transform, operand.vector)};
	}
}

#endif /* GEOMETRY_TRANSFORM_H */
