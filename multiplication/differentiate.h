#ifndef MULTIPLICATION_DIFFERENTIATE_H
#define MULTIPLICATION_DIFFERENTIATE_H 

#include"operation.h"
#include"power.h"
#include"../addition/differentiate.h"

namespace godefv::math{
	// (xy)'=x'y+xy'
	template<class A, class B>
	auto constexpr differentiate(Symbol auto variable, group::generated_by_operation_t<mult_operation_t, A, B> const& ab){
		return ab.first*differentiate(variable, ab.second)+differentiate(variable, ab.first)*ab.second;
	}

	// (x^y)'=yx'(x^(y-1)) if x,x',y commute
	template<Scalar Y, Scalar X>
	auto constexpr differentiate(Symbol auto variable, group::generated_power_t<mult_operation_t, Y, X> const& x_pow_y){
		using group::power;
		return x_pow_y.exponent*differentiate(variable, x_pow_y.operand)*power(mult_operation_t{}, x_pow_y.exponent-one, x_pow_y.operand);
	}
}

#endif /* MULTIPLICATION_DIFFERENTIATE_H */
