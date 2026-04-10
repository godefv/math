#ifndef MULTIPLICATION_REVERSE_H
#define MULTIPLICATION_REVERSE_H 

#include"operation.h"

namespace godefv::math{
	template<class A>
	constexpr auto reverse(A const& a){
		return a;
	}
	template<class A, class B>
	constexpr auto reverse(group::generated_by_operation_t<mult_operation_t, A,B> const& ab){
		return reverse(ab.second)*reverse(ab.first);
	}
	//linear rules
	template<class A, class B>
	constexpr auto reverse(group::generated_by_operation_t<add_operation_t, A,B> const& ab){
		return reverse(ab.first)+reverse(ab.second);
	}
	template<SimpleScalar K, class X>
	constexpr auto reverse(group::generated_power_t<add_operation_t, K, X> const& kx){
		return kx.exponent*reverse(kx.operand);
	}
}

#endif /* MULTIPLICATION_REVERSE_H */
