#ifndef MULTIPLICATION_DIFFERENTIATE_H
#define MULTIPLICATION_DIFFERENTIATE_H 

#include"operation.h"
#include"power.h"
#include"../addition/differentiate.h"

namespace godefv::math{
	// (xy)'=x'y+xy'
	auto constexpr differentiate(Symbol auto variable, group::generated_by_operation_t<mult_operation_t, auto, auto> const& ab){
		return ab.first*differentiate(variable, ab.second)+differentiate(variable, ab.first)*ab.second;
	}

	// (x^y)'=yx'(x^(y-1)) if x,x',y commute
	template<Scalar ScalarOperandT>
	auto constexpr differentiate(Symbol auto variable, group::generated_power_t<mult_operation_t, Scalar auto, ScalarOperandT> const& operand){
		using group::power;
		return operand.exponent*differentiate(variable, operand.operand)*power(mult_operation_t{}, operand.exponent-one, operand.operand);
	}
}

#endif /* MULTIPLICATION_DIFFERENTIATE_H */
