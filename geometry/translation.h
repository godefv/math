#ifndef TRANSLATION_H
#define TRANSLATION_H 

#include"../vector/basis.h"
#include"../vector/direction.h"
#include"../vector/operation.h"

namespace geometry{
	template<class DirectionT, vector::Scalar LengthT=double>
	struct basis_translation_t: vector::basis_vector_t<DirectionT, LengthT>{};
}

#endif /* TRANSLATION_H */
