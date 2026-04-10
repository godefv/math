#ifndef ADDITION_POWER_H
#define ADDITION_POWER_H 

#include"operation.h"

namespace godefv::math{
	//addition is commutative, so n*(a+b)=n*a+n*b
	template<class A, class B>
	auto constexpr generated_power(add_operation_t, auto exponent, group::generated_by_operation_t<add_operation_t,A,B> const& ab){
		return group::power(add_operation_t{}, exponent, ab.first)
		      +group::power(add_operation_t{}, exponent, ab.second);
	}
	//rationals
	auto constexpr generated_power(add_operation_t, auto exponent, SimpleScalar auto scalar){
		return exponent*scalar;
	}
	//(x^n)^m=x^(nm) even for non integral n,m
	template<Scalar OuterExponentT, Scalar InnerExponentT, class X>
	auto constexpr generated_power(add_operation_t, OuterExponentT m, group::generated_power_t<add_operation_t,InnerExponentT,X> const& x_pow_n){
		return group::power(add_operation_t{}, m*x_pow_n.exponent, x_pow_n.operand);
	}

	//eval
	template<class ExponentT, class X>
	auto constexpr eval_with_data(group::generated_power_t<add_operation_t,ExponentT,X> const& pow, auto const& eval_data){
		return eval_with_data(pow.exponent, eval_data)*eval_with_data(pow.operand, eval_data);
	}

}

#endif /* ADDITION_POWER_H */
