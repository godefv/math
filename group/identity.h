#ifndef IDENTITY_H
#define IDENTITY_H 

#include<type_traits>

namespace group{
	template<template<class A, class B> class BinaryOperator> struct identity_t{};

	template<class> struct is_identity:std::false_type{};
	template<template<class,class> class BinaryOperator> struct is_identity<identity_t<BinaryOperator>>:std::true_type{};
	
	template<class T> concept bool Identity=is_identity<T>::value;

	template<class ElementT, class IdentityT, template<class A, class B> class OperatorT>
	concept bool AbsorbsIdentityElement=std::is_same<OperatorT<ElementT,IdentityT>, ElementT>::value
	                                 && std::is_same<OperatorT<IdentityT,ElementT>, ElementT>::value
									;

} 

#endif /* IDENTITY_H */
