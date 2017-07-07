#ifndef OPERATION_H
#define OPERATION_H 

#include"inverse.h"
#include"identity.h"

#include<type_traits>

namespace group{
	template<template<class,class> class BinaryOperator, class A,class B> struct generated_element_t{};
	template<template<class,class> class BinaryOperator, class> struct is_generated_element:std::false_type{};
	template<template<class,class> class BinaryOperator, class A,class B> struct is_generated_element<BinaryOperator, generated_element_t<BinaryOperator,A,B>>:std::true_type{};
	template<template<class,class> class BinaryOperator, class T> concept bool Generated=is_generated_element<BinaryOperator, T>::value;

	template<template<class,class> class BinaryOperator, class A,class B> struct operation_t{using type=generated_element_t<BinaryOperator,A,B>;};
	//operations with identity
	template<template<class,class> class BinaryOperator, class A> 
	struct operation_t<BinaryOperator, identity_t<BinaryOperator>,A>{using type=A;};
	template<template<class,class> class BinaryOperator, class A> requires !std::is_same<A,identity_t<BinaryOperator>>::value 
	struct operation_t<BinaryOperator, A,identity_t<BinaryOperator>>{using type=A;};
	//operations with inverse //inverse_t<B>,B is covered by A=inverse_t<B>
	template<template<class,class> class BinaryOperator, class A> requires !std::is_same<A,identity_t<BinaryOperator>>::value
	struct operation_t<BinaryOperator, A,inverse_t<BinaryOperator, A>>{using type=identity_t<BinaryOperator>;};
	//associativity	//put everything in normalized from ((AB)C)D...
	template<template<class,class> class BinaryOperator, class A,class B,class C> 
		requires !std::is_same<A,identity_t<BinaryOperator>>::value
		      && !std::is_same<inverse_t<BinaryOperator, A>,generated_element_t<BinaryOperator,B,C>>::value
	struct operation_t<BinaryOperator, A,generated_element_t<BinaryOperator,B,C>>: BinaryOperator<typename BinaryOperator<A,B>::type,C>{};
	//collapse operations as much as possible
	template<template<class,class> class BinaryOperator, class A,class B,class C> 
		requires !Generated<BinaryOperator,B> 
		      && !Generated<BinaryOperator,C> 
			  && !Generated<BinaryOperator,typename BinaryOperator<B,C>::type> 
			  && !std::is_same<C,identity_t<BinaryOperator>>::value
			  && !std::is_same<C,inverse_t<BinaryOperator, generated_element_t<BinaryOperator,A,B>>>::value
	struct operation_t<BinaryOperator, generated_element_t<BinaryOperator,A,B>,C>: BinaryOperator<A,typename BinaryOperator<B,C>::type>{};
	
	
	//inverses
	template<template<class,class> class BinaryOperator, class A,class B> 
	struct inverse_impl_t<BinaryOperator, generated_element_t<BinaryOperator, A,B>>: BinaryOperator<inverse_t<BinaryOperator, B>,inverse_t<BinaryOperator, A>>{};

}

#endif /* OPERATION_H */
