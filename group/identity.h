#ifndef IDENTITY_H
#define IDENTITY_H 

#include<type_traits>

namespace group{
	template<template<class A, class B> class BinaryOperator> struct identity_t{};

	template<class ElementT, class IdentityT, template<class A, class B> class OperatorT>
	concept bool AbsorbsIdentityElement=std::is_same<OperatorT<ElementT,IdentityT>, ElementT>::value
	                                 && std::is_same<OperatorT<IdentityT,ElementT>, ElementT>::value
									;
} 

#endif /* IDENTITY_H */
