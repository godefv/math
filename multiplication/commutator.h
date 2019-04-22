#ifndef COMMUTATOR_OPERATION_H
#define COMMUTATOR_OPERATION_H 

#include"operation.h"
#include"../scalar.h"

namespace godefv::math{
	//commutator uses bilinear rules, then ab-ba
	struct commutator_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return commutator(a,b);
		}
	};

	auto constexpr commutator(auto const& a, auto const& b){
		return bilinear_operation_t<commutator_operation_t>::apply(a,b);
	}
	template<class A, class B>
		requires !group::Generated<add_operation_t,A>
		      && !group::Generated<add_operation_t,B>
	auto constexpr commutator(A const& a, B const& b){
		if constexpr(Scalar<A> || Scalar<B>){
			return zero;
		}else{
			return a*b-b*a;
		}
	}

	//anticommutator uses bilinear rules, then ab-ba
	struct anticommutator_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return anticommutator(a,b);
		}
	};

	auto constexpr anticommutator(auto const& a, auto const& b){
		return bilinear_operation_t<anticommutator_operation_t>::apply(a,b);
	}
	template<class A, class B>
		requires !group::Generated<add_operation_t,A>
		      && !group::Generated<add_operation_t,B>
	auto constexpr anticommutator(A const& a, B const& b){
		return a*b+b*a;
	}
}

#endif /* COMMUTATOR_OPERATION_H */
