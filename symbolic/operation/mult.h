#ifndef SYMBOLIC_OPERATION_MULT_H
#define SYMBOLIC_OPERATION_MULT_H 

#include"pow.h"
#include"template.h"

namespace symbolic{
	struct mult_operation_t;

	template<class T> requires group::Generated<mult_operation_t,T> struct is_symbol<T>: std::true_type{};


	//operator - group rules
	template<Symbol Symbol1, Symbol Symbol2> requires !(Ratio<Symbol1> && Ratio<Symbol2>)
	constexpr auto operator*(Symbol1 const& a, Symbol2 const& b){
		return group::operation<mult_operation_t>(a,b);
	}
   	//operator - commutations rules
	template<Symbol A, Symbol B> 
		requires !(Ratio<A> && Ratio<B>)
   		      && static_compare(A{},B{})<0
   	constexpr auto operator*(A const& a, B const& b){
   		return b*a;
   	}

	//mult operation
	struct mult_operation_t{
		static constexpr auto apply(auto const& a, auto const& b){
			return a*b;
		}

		//group inverse
		static constexpr auto inverse(auto const& a){
			//return group::inverse<mult_operation_t>(a);
			return symbolic::inverse(a);
		}
	};
	
	//formatting
	std::ostream& operator<<(std::ostream& out, group::generated_by_operation_t<mult_operation_t, auto, auto> const& ab){
		return out<<"("<<ab.first<<") * ("<<ab.second<<")";
	}
}

#endif /* SYMBOLIC_OPERATION_MULT_H */
