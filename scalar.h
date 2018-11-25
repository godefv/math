#ifndef SCALAR_H
#define SCALAR_H 

#include"symbolic/rational.h"

#include<type_traits>

namespace math{
	//!A Scalar is a type representing a mathematical expression, the product of which with anything commutes.

	template<class T> concept bool SimpleScalar=Number<T> || Ratio<T>;

	template<class T> struct is_scalar:std::false_type{};
	template<SimpleScalar SimpleScalarT> struct is_scalar<SimpleScalarT>:std::true_type{};

	template<class T> concept bool Scalar=is_scalar<T>::value;
	template<class T> concept bool Zero=is_zero<T>::value;
	template<class T> concept bool NonZero=!is_zero<T>::value;
	template<class T> concept bool NonZeroScalar=Scalar<T> && !Zero<T>;
}

#endif /* SCALAR_H */
