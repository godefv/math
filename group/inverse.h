#ifndef INVERSE_H
#define INVERSE_H 

#include"identity.h"

namespace group{
	//inverse generates a new type by default
	template<class T> struct generated_inverse_t{};
	template<class T> struct inverse_impl_t{using type=generated_inverse_t<T>;};
	//inverse of inverse is self
	template<class T> struct inverse_impl_t<generated_inverse_t<T>>{using type=T;};
	//inverse of identity is identity
	template<template<class,class> class BinaryOperator> struct inverse_impl_t<identity_t<BinaryOperator>>{using type=identity_t<BinaryOperator>;};

	template<class T> using inverse_t=typename inverse_impl_t<T>::type;

	template<class ElementT, class IdentityT, template<class A, class B> class OperatorT, template<class A> class InverseT>
	concept bool HasInverse=std::is_same<InverseT<InverseT<ElementT>>, ElementT>::value
	                     && std::is_same<OperatorT<InverseT<ElementT>,ElementT>, IdentityT>::value
	                     && std::is_same<OperatorT<ElementT,InverseT<ElementT>>, IdentityT>::value
	                     && AbsorbsIdentityElement<InverseT<ElementT>,IdentityT,OperatorT>
                         ;
} 

#endif /* INVERSE_H */
