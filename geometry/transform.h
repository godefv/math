#ifndef GEOMETRY_TRANSFORM_H
#define GEOMETRY_TRANSFORM_H 

#include"rotation.h"
#include"homothecy.h"
#include"translation.h"

namespace math::geometry{
	auto constexpr apply(Homothecy const& homothecy, translation_t<auto> const& operand){
		return translation_t{apply(homothecy, operand.vector)};
	}
}

#endif /* GEOMETRY_TRANSFORM_H */
