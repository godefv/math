#ifndef ROTATION_H
#define ROTATION_H 

#include"../vector/basis.h"
#include"../vector/direction.h"

namespace geometry{
	template<class PlaneT, vector::Scalar AngleT=double>
	struct basis_rotation_t: vector::basis_element_t<PlaneT, AngleT>{};
}

#endif /* ROTATION_H */
