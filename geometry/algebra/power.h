#ifndef GEOMETRY_ALGEBRA_POWER_H
#define GEOMETRY_ALGEBRA_POWER_H 

#include"definition.h"
#include"grade.h"

namespace godefv::math::geometry{
	//cyclic order
	template<class Name>
	auto constexpr cycle_order(mult_operation_t, direction_positive_t<Name>){
		return 2;
	}
	template<class Name>
	auto constexpr cycle_order(mult_operation_t, direction_negative_t<Name>){
		return 4;
	}

	template<class Name>
	auto constexpr generated_power(mult_operation_t, integer_t<2>, direction_negative_t<Name> const&){
		return -one;
	}
	template<class Name>
	auto constexpr generated_power(mult_operation_t, integer_t<3>, direction_negative_t<Name> const& ei){
		return -ei;
	}
	template<class Name>
	auto constexpr generated_power(mult_operation_t, integer_t<2>, direction_null_t<Name> const&){
		return zero;
	}
	template<MultiVector MultiVectorT> 
	requires (NonZeroScalar<decltype(square(MultiVectorT{}))> //user is responsible for division by zero errors
			&& !group::Power<MultiVectorT,add_operation_t> //handled by multiplication/power.h
	)
	auto constexpr generated_power(mult_operation_t, integer_t<-1>, MultiVectorT const& operand){
		return operand/project(square(operand), grades<0>());
	}
}

#endif /* GEOMETRY_ALGEBRA_POWER_H */
