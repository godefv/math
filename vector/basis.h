#ifndef BASIS_H
#define BASIS_H 

#include"scalar.h"

namespace vector{
	template<class ElementT, Scalar ScalarT=double> 
	struct basis_element_t{
		ScalarT coordinate;
	};
}

#endif /* BASIS_H */
