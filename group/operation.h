#ifndef OPERATION_H
#define OPERATION_H 

#include"apply_operation.h"
#include"inverse.h"
#include"identity.h"
#include"minus.h"

#include<type_traits>

namespace group{
	template<class Operator, class A,class B,class...> struct generated_element_t{A first; B second;};
	//is_generated_element
	template<class Operator, class> struct is_generated_element:std::false_type{};
	template<class Operator, class A,class B,class... C> struct is_generated_element<Operator, generated_element_t<Operator,A,B,C...>>:std::true_type{};
	template<class Operator, class T> concept bool Generated=is_generated_element<Operator, T>::value;

	template<class Operator, class A,class B> 
	constexpr auto operation(A const& a, B const& b){return generated_element_t<Operator,A,B>{a,b};}

	//operations with identity
	template<class Operator, class A> 
	constexpr auto operation(identity_t<Operator> const&, A const& a){return a;}
	template<class Operator, class A> requires !std::is_same<A,identity_t<Operator>>::value 
	constexpr auto operation(A const& a, identity_t<Operator> const&){return a;}
	//operations with inverse //inverse_t<B>,B is covered by A=inverse_t<B>
	template<class Operator, class A> requires !std::is_same<A,identity_t<Operator>>::value
	constexpr auto operation(A const&, inverse_t<Operator, A> const&){return identity_t<Operator>{};}
	//operations with minus
	template<class Operator, class A,class B> 
		requires !std::is_same<generated_minus_t<Operator, B>, inverse_t<Operator, A>>::value
		      && !std::is_same<A, identity_t<Operator>>::value
	constexpr auto operation(A const&, generated_minus_t<Operator, B> const&){
		return group::minus_t<Operator, decltype(apply_operation<Operator>(A{},B{}))>{};
	}
	template<class Operator, class A,class B> 
		requires !std::is_same<generated_minus_t<Operator, B>, inverse_t<Operator, A>>::value
		      && !std::is_same<A, identity_t<Operator>>::value
			  && !Minus<Operator,A>
	constexpr auto operation(generated_minus_t<Operator, B> const&, A const&){
		return group::minus_t<Operator, decltype(apply_operation<Operator>(B{},A{}))>{};
	}
	//associativity	//put everything in normalized from ((AB)C)D...
	template<class Operator, class A,class B,class C> 
		requires !std::is_same<A,identity_t<Operator>>::value
		      && !std::is_same<inverse_t<Operator, A>,generated_element_t<Operator,B,C>>::value
			  && !Minus<Operator,A>
	constexpr auto operation(A const& a, generated_element_t<Operator,B,C> const& bc){
		return apply_operation<Operator>(apply_operation<Operator>(a, bc.first), bc.second);
	}
	//collapse operations as much as possible
	template<class Operator, class A,class B,class C> 
		requires !Generated<Operator,B> 
		      && !Generated<Operator,C> 
			  && !Generated<Operator,decltype(apply_operation<Operator>(B{},C{}))> 
			  && !Minus    <Operator,C>
			  && !std::is_same<C,identity_t<Operator>>::value
			  && !std::is_same<C,inverse_t<Operator, generated_element_t<Operator,A,B>>>::value
	constexpr auto operation(generated_element_t<Operator,A,B> const& ab, C const& c){
		return apply_operation<Operator>(ab.first, apply_operation<Operator>(ab.second,c));
	}

	//inverse of product
	template<class Operator, class A,class B> 
	constexpr auto inverse(generated_element_t<Operator, A,B> const& ab){
		return apply_operation<Operator>(Operator::inverse(ab.second), Operator::inverse(ab.first));
	}
	//inverse of minus A
	template<class Operator, class A> 
	constexpr auto inverse(generated_minus_t<Operator, A> const& a){
		return minus_t<Operator, decltype(Operator::inverse(a.value))>{};
	}

}

#endif /* OPERATION_H */
