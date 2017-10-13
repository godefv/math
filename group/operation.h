#ifndef OPERATION_H
#define OPERATION_H 

#include"inverse.h"
#include"identity.h"
#include"minus.h"
#include"../symbolic/eval.h"

#include<type_traits>

namespace group{
	template<class Operator, class A,class B> struct generated_element_t{
		Operator operation;
		A first; B second;
	};
	template<class Operator, class A,class B> generated_element_t(Operator,A,B)->generated_element_t<Operator,A,B>;

	auto constexpr eval(generated_element_t<auto,auto,auto> const& a){
		using ::eval;
		return std::decay_t<decltype(a.operation)>::apply(eval(a.first), eval(a.second));
	}

	//is_generated_element
	template<class Operator, class> struct is_generated_element:std::false_type{};
	template<class Operator, class A,class B> struct is_generated_element<Operator, generated_element_t<Operator,A,B>>:std::true_type{};
	template<class Operator, class T> concept bool Generated=is_generated_element<Operator, T>::value;

	template<class Operator, class A,class B>
	bool operator==(generated_element_t<Operator, A,B> const& a, generated_element_t<Operator, A,B> const& b){
		return a.first==b.first && a.second==b.second;
	}
	bool operator==(generated_element_t<auto, auto,auto> const& a, generated_element_t<auto, auto,auto> const& b){
		return false;
	}
	bool operator!=(generated_element_t<auto, auto,auto> const& a, generated_element_t<auto, auto,auto> const& b){
		return !(a==b);
	}

	//default operation
	template<class Operator, class A,class B> 
	constexpr auto operation(A const& a, B const& b){return generated_element_t{Operator{},a,b};}
	//operations with identity
	template<class Operator, class A> 
	constexpr auto operation(identity_t<Operator> const&, A const& a){return a;}
	template<class Operator, class A> requires !std::is_same<A,identity_t<Operator>>::value 
	constexpr auto operation(A const& a, identity_t<Operator> const&){return a;}
	//operations with inverse //inverse_t<B>,B is covered by A=inverse_t<B>
	template<class Operator, class A> 
		requires !std::is_same<A,identity_t<Operator>>::value
		      && !Generated<Operator, A> //without this, we return identity even with non constexpr arguments, regardless of their value
	constexpr auto operation(A const&, inverse_t<Operator, A> const&){return identity_t<Operator>{};}
	//operations with minus
	template<class Operator, class A,class B> 
		requires !std::is_same<A, identity_t<Operator>>::value
		      && !(std::is_same<generated_minus_t<Operator, B>, inverse_t<Operator, A>>::value && !Generated<Operator, A>)
	constexpr auto operation(A const&, generated_minus_t<Operator, B> const&){
		return group::minus_t<Operator, decltype(Operator::apply(A{},B{}))>{};
	}
	template<class Operator, class A,class B> 
		requires !std::is_same<A, identity_t<Operator>>::value
		      && !std::is_same<A, inverse_t<Operator, generated_minus_t<Operator, B>>>::value
			  && !Minus<Operator,A>
	constexpr auto operation(generated_minus_t<Operator, B> const&, A const&){
		return group::minus_t<Operator, decltype(Operator::apply(B{},A{}))>{};
	}
	//associativity	//put everything in normalized from ((AB)C)D...
	template<class Operator, class A,class B,class C> 
		requires !std::is_same<A,identity_t<Operator>>::value
		      && !(std::is_same<generated_element_t<Operator,B,C>, inverse_t<Operator, A>>::value && !Generated<Operator, A>)
			  && !Minus<Operator,A>
	constexpr auto operation(A const& a, generated_element_t<Operator,B,C> const& bc){
		return Operator::apply(Operator::apply(a, bc.first), bc.second);
	}
	//collapse operations as much as possible
	template<class Operator, class A,class B,class C> 
		requires !Generated<Operator,B> 
		      && !Generated<Operator,C> 
			  && !Minus    <Operator,C>
			  && !std::is_same<decltype(Operator::apply(B{},C{})), generated_element_t<Operator,B,C>>::value 
			  && !std::is_same<C,identity_t<Operator>>::value
	constexpr auto operation(generated_element_t<Operator,A,B> const& ab, C const& c){
		return Operator::apply(ab.first, Operator::apply(ab.second,c));
	}

	//inverse of product
	template<class Operator, class A,class B> 
	constexpr auto inverse(generated_element_t<Operator, A,B> const& ab){
		return Operator::apply(Operator::inverse(ab.second), Operator::inverse(ab.first));
	}
	//inverse of minus A
	template<class Operator, class A> 
	constexpr auto inverse(generated_minus_t<Operator, A> const& a){
		return minus_t<Operator, decltype(Operator::inverse(a.value))>{};
	}

}

#endif /* OPERATION_H */
