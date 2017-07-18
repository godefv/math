#ifndef OPERATION_H
#define OPERATION_H 

#include"inverse.h"
#include"identity.h"
#include"minus.h"

#include<type_traits>

namespace group{
	template<template<class,class> class BinaryOperator, class A,class B,class...> struct generated_element_t{A first; B second;};
	//is_generated_element
	template<template<class,class> class BinaryOperator, class> struct is_generated_element:std::false_type{};
	template<template<class,class> class BinaryOperator, class A,class B,class... C> struct is_generated_element<BinaryOperator, generated_element_t<BinaryOperator,A,B,C...>>:std::true_type{};
	template<template<class,class> class BinaryOperator, class T> concept bool Generated=is_generated_element<BinaryOperator, T>::value;

	template<template<class,class> class BinaryOperator, class A,class B> 
	constexpr auto operation(A const& a, B const& b){return generated_element_t<BinaryOperator,A,B>{a,b};}

	template<template<class,class> class BinaryOperator, class A, class B> 
	constexpr auto apply_operation(A const& a, B const& b){return BinaryOperator<A,B>::apply(a,b);}

	//operations with identity
	template<template<class,class> class BinaryOperator, class A> 
	constexpr auto operation(identity_t<BinaryOperator> const&, A const& a){return a;}
	template<template<class,class> class BinaryOperator, class A> requires !std::is_same<A,identity_t<BinaryOperator>>::value 
	constexpr auto operation(A const& a, identity_t<BinaryOperator> const&){return a;}
	//operations with inverse //inverse_t<B>,B is covered by A=inverse_t<B>
	template<template<class,class> class BinaryOperator, class A> requires !std::is_same<A,identity_t<BinaryOperator>>::value
	constexpr auto operation(A const&, inverse_t<BinaryOperator, A> const&){return identity_t<BinaryOperator>{};}
	//operations with minus
	template<template<class,class> class BinaryOperator, class A,class B> 
		requires !std::is_same<generated_minus_t<BinaryOperator, B>, inverse_t<BinaryOperator, A>>::value
		      && !std::is_same<A, identity_t<BinaryOperator>>::value
	constexpr auto operation(A const&, generated_minus_t<BinaryOperator, B> const&){
		return group::minus_t<BinaryOperator, decltype(apply_operation<BinaryOperator>(A{},B{}))>{};
	}
	template<template<class,class> class BinaryOperator, class A,class B> 
		requires !std::is_same<generated_minus_t<BinaryOperator, B>, inverse_t<BinaryOperator, A>>::value
		      && !std::is_same<A, identity_t<BinaryOperator>>::value
			  && !Minus<BinaryOperator,A>
	constexpr auto operation(generated_minus_t<BinaryOperator, B> const&, A const&){
		return group::minus_t<BinaryOperator, decltype(apply_operation<BinaryOperator>(B{},A{}))>{};
	}
	//associativity	//put everything in normalized from ((AB)C)D...
	template<template<class,class> class BinaryOperator, class A,class B,class C> 
		requires !std::is_same<A,identity_t<BinaryOperator>>::value
		      && !std::is_same<inverse_t<BinaryOperator, A>,generated_element_t<BinaryOperator,B,C>>::value
			  && !Minus<BinaryOperator,A>
	constexpr auto operation(A const& a, generated_element_t<BinaryOperator,B,C> const& bc){
		return apply_operation<BinaryOperator>(apply_operation<BinaryOperator>(a, bc.first), bc.second);
	}
	//collapse operations as much as possible
	template<template<class,class> class BinaryOperator, class A,class B,class C> 
		requires !Generated<BinaryOperator,B> 
		      && !Generated<BinaryOperator,C> 
			  && !Generated<BinaryOperator,decltype(apply_operation<BinaryOperator>(B{},C{}))> 
			  && !Minus    <BinaryOperator,C>
			  && !std::is_same<C,identity_t<BinaryOperator>>::value
			  && !std::is_same<C,inverse_t<BinaryOperator, generated_element_t<BinaryOperator,A,B>>>::value
	constexpr auto operation(generated_element_t<BinaryOperator,A,B> const& ab, C const& c){
		return apply_operation<BinaryOperator>(ab.first, apply_operation<BinaryOperator>(ab.second,c));
	}

	//operation_t
	template<template<class,class> class BinaryOperator, class A,class B> struct operation_t{using type=decltype(operation<BinaryOperator>(std::declval<A>(), std::declval<B>()));};

	//template<template<class,class> class BinaryOperator, class A,class B,class C> 
		//requires !Generated<BinaryOperator,B> 
			  //&& !Generated<BinaryOperator,C> 
			  //&&  Generated<BinaryOperator,decltype(apply_operation<BinaryOperator>(B{},C{}))> 
			  //&& !std::is_same<C,identity_t<BinaryOperator>>::value
	//struct operation_t<BinaryOperator, generated_element_t<BinaryOperator,A,B>,C>{using type=generated_element_t<BinaryOperator,A,B,C>;};
	
	
	//inverses
	template<template<class,class> class BinaryOperator, class A,class B> 
	struct inverse_impl_t<BinaryOperator, generated_element_t<BinaryOperator, A,B>>{using type=decltype(apply_operation<BinaryOperator>(inverse_t<BinaryOperator, B>{},inverse_t<BinaryOperator, A>{}));};
	//inverse of minus A
	template<template<class,class> class BinaryOperator, class A> 
	struct inverse_impl_t<BinaryOperator, generated_minus_t<BinaryOperator, A>>: minus_impl_t<BinaryOperator, inverse_t<BinaryOperator, A>>{};

}

#endif /* OPERATION_H */
