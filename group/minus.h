#ifndef MINUS_H
#define MINUS_H 

#include"inverse.h"

namespace group{
	//! minus one commutes with every other element and squares to one under BinaryOperator 
	//! minus_t<BinaryOperator, A> equals minus one times A under BinaryOperator
	template<template<class,class> class BinaryOperator, class A> struct generated_minus_t{};
	template<template<class,class> class BinaryOperator, class A> struct minus_impl_t{using type=generated_minus_t<BinaryOperator, A>;};
	template<template<class,class> class BinaryOperator, class A> struct minus_impl_t<BinaryOperator, generated_minus_t<BinaryOperator, A>>{using type=A;};
	template<template<class,class> class BinaryOperator, class A> using minus_t=typename minus_impl_t<BinaryOperator, A>::type;

	template<template<class,class> class BinaryOperator, class> struct is_generated_minus:std::false_type{};
	template<template<class,class> class BinaryOperator, class A> struct is_generated_minus<BinaryOperator, generated_minus_t<BinaryOperator,A>>:std::true_type{};
	template<template<class,class> class BinaryOperator, class T> concept bool Minus=is_generated_minus<BinaryOperator, T>::value;
}

#endif /* MINUS_H */
