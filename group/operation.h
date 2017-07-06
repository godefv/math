#ifndef OPERATION_H
#define OPERATION_H 

#include"inverse.h"
#include"identity.h"

#include<type_traits>

namespace group{
	template<template<class,class> class BinaryOperator, class A,class B> struct generated_element_t{};
	template<class> struct is_generated_element:std::false_type{};
	template<template<class,class> class BinaryOperator, class A,class B> struct is_generated_element<generated_element_t<BinaryOperator,A,B>>:std::true_type{};
	template<class T> concept bool Generated=is_generated_element<T>::value;

	template<template<class,class> class BinaryOperator, class A,class B> struct operation_t{using type=generated_element_t<BinaryOperator,A,B>;};
	//oparations with identity
	template<template<class,class> class BinaryOperator, class A> struct operation_t<BinaryOperator, identity_t<BinaryOperator>,A>{using type=A;};
	template<template<class,class> class BinaryOperator, class A> struct operation_t<BinaryOperator, A,identity_t<BinaryOperator>>{using type=A;};
	//operations with inverse //inverse_t<B>,B is covered by A=inverse_t<B>
	template<template<class,class> class BinaryOperator, class A> struct operation_t<BinaryOperator, A,inverse_t<A>>{using type=identity_t<BinaryOperator>;};
	//associativity	//put everything in normalized from ((AB)C)D...
	template<template<class,class> class BinaryOperator, class A,class B,class C> requires !Identity<A>
	struct operation_t<BinaryOperator, A,generated_element_t<BinaryOperator,B,C>>: BinaryOperator<typename BinaryOperator<A,B>::type,C>{};
	//collapse operations as much as possible
	template<template<class,class> class BinaryOperator, class A,class B,class C> requires !Generated<B> && !Generated<C> && !Generated<typename BinaryOperator<B,C>::type> && !Identity<C>
	struct operation_t<BinaryOperator, generated_element_t<BinaryOperator,A,B>,C>: BinaryOperator<A,typename BinaryOperator<B,C>::type>{};
	
}

#endif /* OPERATION_H */
