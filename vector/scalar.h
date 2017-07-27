#ifndef SCALAR_H
#define SCALAR_H 

#include<type_traits>

namespace vector{
	template<class ScalarT>
	concept bool Scalar=std::is_arithmetic<ScalarT>::value;
}

#endif /* SCALAR_H */
