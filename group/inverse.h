#ifndef INVERSE_H
#define INVERSE_H 

#include"identity.h"

namespace group{
	template<class T> struct generated_inverse_t{};
	template<class T> struct inverse_impl_t{using type=generated_inverse_t<T>;};
	template<class T> struct inverse_impl_t<generated_inverse_t<T>>{using type=T;};
	template<template<class,class> class BinaryOperator> struct inverse_impl_t<identity_t<BinaryOperator>>{using type=identity_t<BinaryOperator>;};
	template<class T> using inverse_t=typename inverse_impl_t<T>::type;
} 

#endif /* INVERSE_H */
