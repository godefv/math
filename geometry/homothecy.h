#ifndef GEOMETRY_HOMOTHECY_H
#define GEOMETRY_HOMOTHECY_H 

#include"composition.h"

namespace math::geometry{
	auto homothecy(Point const& point, Scalar const& ratio){
		//TODO
		return translation_t{},scaling_t{ratio},translation_t{};
	}
}

#endif /* GEOMETRY_HOMOTHECY_H */
