#ifndef MINUS_H
#define MINUS_H 

#include"inverse.h"

#include<iostream>

namespace group{
	//! minus one commutes with every other element and squares to one under Operator 
	//! minus_t<Operator, A> equals minus one times A under Operator
	template<class Operator, class A> struct generated_minus_t{A value;};

	template<class Operator> constexpr auto minus(auto const& a){
		return generated_minus_t<Operator, std::decay_t<decltype(a)>>{a};
	}
	template<class Operator> constexpr auto minus(generated_minus_t<Operator,auto> const& a){
		return a.value;
	}
	template<class Operator, class A> using minus_t=decltype(minus<Operator>(A{}));

	template<class Operator, class> struct is_generated_minus:std::false_type{};
	template<class Operator, class A> struct is_generated_minus<Operator, generated_minus_t<Operator,A>>:std::true_type{};
	template<class Operator, class T> concept bool Minus=is_generated_minus<Operator, T>::value;

	template<class Operator, class T>
	bool constexpr operator==(generated_minus_t<Operator, T> const& a, generated_minus_t<Operator, T> const& b){
		return a.value==b.value;
	}
	template<class Operator, class T>
	bool constexpr operator!=(generated_minus_t<Operator, T> const& a, generated_minus_t<Operator, T> const& b){
		return !(a==b);
	}

	std::ostream& operator<<(std::ostream& out, generated_minus_t<auto, auto> const& a){
		return out<<"-("<<a.value<<")";
	}
}

#endif /* MINUS_H */
