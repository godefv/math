#ifndef MULTIPLICATION_REVERSE_H
#define MULTIPLICATION_REVERSE_H 

#include"operation.h"

namespace godefv::math{
	constexpr auto reverse(auto const& a){
		return a;
	}
	constexpr auto reverse(group::generated_by_operation_t<mult_operation_t, auto,auto> const& ab){
		return reverse(ab.second)*reverse(ab.first);
	}
	//linear rules
	constexpr auto reverse(group::generated_by_operation_t<add_operation_t, auto,auto> const& ab){
		return reverse(ab.first)+reverse(ab.second);
	}
	constexpr auto reverse(group::generated_power_t<add_operation_t, SimpleScalar, auto> const& kx){
		return kx.exponent*reverse(kx.operand);
	}
}

#endif /* MULTIPLICATION_REVERSE_H */
