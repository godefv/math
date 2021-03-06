#ifndef SCALAR_H
#define SCALAR_H 

#include<type_traits>

namespace godefv::math{
	//!A Scalar is a type representing a mathematical expression, the product of which with anything commutes.

	template<class T> concept Number=std::is_arithmetic<T>::value;

	template<class T> struct is_simple_scalar:std::false_type{};
	template<Number NumberT> struct is_simple_scalar<NumberT>:std::true_type{};
	template<class T> concept SimpleScalar=is_simple_scalar<T>::value;
	template<class T> concept NonSimpleScalar=!SimpleScalar<T>;

	template<class T> struct is_scalar:std::false_type{};
	template<SimpleScalar SimpleScalarT> struct is_scalar<SimpleScalarT>:std::true_type{};

	template<class T> concept Scalar=SimpleScalar<T> || is_scalar<T>::value;
	template<class T> concept NonScalar=NonSimpleScalar<T> && !is_scalar<T>::value;
}

#endif /* SCALAR_H */
