#ifndef SYMBOLIC_OPERATION_MULT_H
#define SYMBOLIC_OPERATION_MULT_H 

#include"template.h"

namespace symbolic{
	//mult operation
	struct mult_operation_t{
		//commutations rules
		template<class A,class B> 
			requires Operation<A>
			      && Operation<B>
			      && static_compare(A{},B{})<0
		static constexpr auto apply(A const& a, B const& b){
			return apply(b,a);
		}
		//group rules
		template<class A,class B> 
		static constexpr auto apply(A const& a, B const& b){
			return group::operation<mult_operation_t>(a,b);
		}
		vector::Scalar{Scalar2}
		static constexpr auto apply(vector::Scalar const& a, Scalar2 const& b){
			return a*b;
		}

		//group inverse
		template<class A>
		static constexpr auto inverse(A const& a){return group::inverse<mult_operation_t>(a);}
	};
	//operators
	Operation{Operation2}
	constexpr auto operator*(Operation const& a, Operation2 const& b){
		return mult_operation_t::apply(a,b);
	}

	//formatting
	std::ostream& operator<<(std::ostream& out, group::generated_by_operation_t<mult_operation_t, auto, auto> const& ab){
		return out<<"("<<ab.first<<") * ("<<ab.second<<")";
	}
}

#endif /* SYMBOLIC_OPERATION_MULT_H */
