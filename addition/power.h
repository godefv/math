#ifndef ADDITION_POWER_H
#define ADDITION_POWER_H 

#include"operation.h"

namespace godefv::math{
	//addition is commutative, so n*(a+b)=n*a+n*b
	auto constexpr generated_power(add_operation_t, auto exponent, group::generated_by_operation_t<add_operation_t,auto,auto> const& ab){
		return group::power(add_operation_t{}, exponent, ab.first)
		      +group::power(add_operation_t{}, exponent, ab.second);
	}
	//rationals
	auto constexpr generated_power(add_operation_t, auto exponent, SimpleScalar auto scalar){
		return exponent*scalar;
	}
	//(x^n)^m=x^(nm) even for non integral n,m 
	template<Scalar Exponent1, Scalar Exponent2> 
	auto constexpr generated_power(add_operation_t, Exponent1 exponent, group::generated_power_t<add_operation_t,Exponent2,auto> const& operand){
		return group::power(add_operation_t{}, exponent*operand.exponent, operand.operand);
	} 

	//eval
	auto constexpr eval_with_data(group::generated_power_t<add_operation_t,auto,auto> const& pow, auto const& eval_data){
		return eval_with_data(pow.exponent, eval_data)*eval_with_data(pow.operand, eval_data);
	}

}

#endif /* ADDITION_POWER_H */
