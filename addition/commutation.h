#ifndef ADDITION_COMMUTATION_H
#define ADDITION_COMMUTATION_H 

#include"operation.h"
#include"../group/commutation.h"

namespace math{
	template<class T> requires !group::Power<add_operation_t,T>
	int constexpr static_compare(auto op, group::generated_power_t<add_operation_t, SimpleScalar, auto> const& a, T const& b){
		return static_compare(op,a.operand,b);
	}
	template<class T> requires !group::Power<add_operation_t,T>
	int constexpr static_compare(auto op, T const& a, group::generated_power_t<add_operation_t, SimpleScalar, auto> const& b){
		return static_compare(op,a,b.operand);
	}
}

#endif /* ADDITION_COMMUTATION_H */
