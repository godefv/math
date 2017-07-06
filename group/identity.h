#ifndef IDENTITY_H
#define IDENTITY_H 

#include<type_traits>

namespace group{
	template<template<class A, class B> class BinaryOperator> struct identity_t{};
	template<class> struct is_identity:std::false_type{};
	template<template<class,class> class BinaryOperator> struct is_identity<identity_t<BinaryOperator>>:std::true_type{};
	template<class T> concept bool Identity=is_identity<T>::value;
} 

#endif /* IDENTITY_H */
