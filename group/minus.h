#ifndef MINUS_H
#define MINUS_H 

#include"inverse.h"

#include<iostream>

namespace group{
	//! minus one commutes with every other element and squares to one under Operator 
	//! minus_t<Operator, A> equals minus one times A under Operator
	template<class Operator, class A> struct generated_minus_t{A value;};
	template<class Operator, class A> struct minus_impl_t{using type=generated_minus_t<Operator, A>;};
	template<class Operator, class A> struct minus_impl_t<Operator, generated_minus_t<Operator, A>>{using type=A;};
	template<class Operator, class A> using minus_t=typename minus_impl_t<Operator, A>::type;

	template<class Operator, class> struct is_generated_minus:std::false_type{};
	template<class Operator, class A> struct is_generated_minus<Operator, generated_minus_t<Operator,A>>:std::true_type{};
	template<class Operator, class T> concept bool Minus=is_generated_minus<Operator, T>::value;

	std::ostream& operator<<(std::ostream& out, generated_minus_t<auto, auto> const& a){
		return out<<"-("<<a.value<<")";
	}
}

#endif /* MINUS_H */
