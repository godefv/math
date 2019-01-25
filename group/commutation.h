#ifndef GROUP_COMMUTATION_H
#define GROUP_COMMUTATION_H 

#include"identity.h"
#include"inverse.h"
#include"operation.h"
#include"../scalar.h"
#include"../name.h"

namespace math{
	template<class OperatorT>
	int constexpr sort_index(OperatorT, group::identity_t<OperatorT> const&){
		return 0;
	}
	int constexpr sort_index(auto, SimpleScalar const&){
		return 10;
	}
	template<Scalar ScalarT> requires !SimpleScalar<ScalarT>
	int constexpr sort_index(auto, ScalarT const&){
		return 20;
	}
	int constexpr sort_index(auto, symbol_t<auto> const&){
		return 30;
	}
	template<class Operator1, class Operator2> requires !std::is_same<Operator1,Operator2>::value
	int constexpr sort_index(Operator1, group::generated_by_operation_t<Operator2, auto,auto> const&){
		return 100;
	}
	template<class OperatorT>
	int constexpr sort_index(OperatorT, auto const&){
		return 200;
	}

	template<class OperatorT>
	auto constexpr sort_as(OperatorT, auto const& a){
		return a;
	}
	template<class OperatorT>
	auto constexpr sort_as(OperatorT op, group::generated_power_t<OperatorT, SimpleScalar, auto> const& pow){
		return sort_as(op, pow.operand);
	}

	template<class OperatorT>
	int constexpr static_compare(OperatorT op, auto const& a, auto const& b){
		return sort_index(op, b)-sort_index(op, a);
	}
	template<class OperatorT, class T1, class T2>
		requires !std::is_same<decltype(sort_as(OperatorT{},std::declval<T1>())), T1>::value
		      || !std::is_same<decltype(sort_as(OperatorT{},std::declval<T2>())), T2>::value
	int constexpr static_compare(OperatorT op, T1 const& a, T2 const& b){
		return static_compare(op, sort_as(op, a), sort_as(op, b));
	}

	//name_t
	constexpr int static_compare(auto, name_t<> const&, name_t<> const&){
		return 0;
	}
	template<char C1, char... Name1>
	constexpr int static_compare(auto, name_t<C1,Name1...> const&, name_t<> const&){
		return -1;
	}
	template<char C1, char... Name1>
	constexpr int static_compare(auto, name_t<> const&, name_t<C1,Name1...> const&){
		return 1;
	}
	template<char C1, char... Name1, char C2, char... Name2>
	constexpr int static_compare(auto const& op, name_t<C1,Name1...> const&, name_t<C2,Name2...> const&){
		if constexpr(C1!=C2){
		   return C2-C1;
		}else{
			return static_compare(op, name_t<Name1...>{}, name_t<Name2...>{});
		}
	}

	//T<name_t<...>>
	template<template<class Name> class T, char... Name1, char... Name2>
	int constexpr static_compare(auto const& op, T<name_t<Name1...>> const& a, T<name_t<Name2...>> const& b){
		return static_compare(op, a.name, b.name);
	}

	//powers
	template<class OperatorT, Ratio Exponent2>
	int constexpr static_compare(auto op, group::generated_power_t<OperatorT, Ratio, auto> const& a, group::generated_power_t<OperatorT, Exponent2, auto> const& b){
		auto operand_order=static_compare(op, a.operand, b.operand);
		if(operand_order!=0){
		   return operand_order;
		}else{
			return (b.exponent-a.exponent).numerator();
		}
	}

	//auto constexpr static_compare(identity_t<auto> const& a, identity_t<auto> const& b){
		//return static_compare(a.operation,b.operation);
	//}
	//auto constexpr static_compare(generated_inverse_t<auto, auto> const& a, generated_inverse_t<auto, auto> const& b){
		//auto constexpr operation_order=static_compare(a.operation,b.operation);
		//if constexpr(operation_order!=0) return operation_order;

		//return static_compare(a.value_before_inverse,b.value_before_inverse);
	//}
	//generated by group operation
	template<class OperatorT>
	auto constexpr static_compare(auto op, group::generated_by_operation_t<OperatorT, auto, auto> const& a, group::generated_by_operation_t<OperatorT, auto, auto> const& b){
		//auto constexpr operation_order=static_compare(a.operation,b.operation);
		//if constexpr(operation_order!=0) return operation_order;

		auto second_order=static_compare(op, a.second,b.second);
		if(second_order!=0) return second_order;

		return static_compare(op, a.first, b.first);
	}
	
}

#endif /* GROUP_COMMUTATION_H */
