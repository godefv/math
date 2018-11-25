#ifndef ADDITION_POWER_H
#define ADDITION_POWER_H 

#include"operation.h"

namespace math{
	//addition is commutative, so n*(a+b)=n*a+n*b
	auto constexpr generated_power(add_operation_t, auto exponent, group::generated_by_operation_t<add_operation_t,auto,auto> const& ab){
		return group::power(add_operation_t{}, exponent, ab.first)
		      +group::power(add_operation_t{}, exponent, ab.second);
	}
	//rationals
	auto constexpr generated_power(add_operation_t, auto exponent, SimpleScalar scalar){
		return exponent*scalar;
	}

	//eval
	auto constexpr eval(group::generated_power_t<add_operation_t,auto,auto> const& pow){
		using ::eval;
		return eval(pow.exponent)*eval(pow.operand);
	}

}

#endif /* ADDITION_POWER_H */
