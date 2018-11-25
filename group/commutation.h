#ifndef GROUP_COMMUTATION_H
#define GROUP_COMMUTATION_H 

#include"identity.h"
#include"inverse.h"
#include"operation.h"
#include"../scalar.h"
#include"../symbolic/symbol.h"

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

	//symbol_t
	template<class Name>
	int constexpr static_compare(auto, symbol_t<Name>, symbol_t<Name>){
		return 0;
	}

	template<char C1, char C2> requires C1!=C2
	int constexpr static_compare(auto, symbol_t<symbol_name_t<C1>>, symbol_t<symbol_name_t<C2>>){
		return C2-C1;
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
	//auto constexpr static_compare(generated_by_operation_t<auto, auto, auto> const& a, generated_by_operation_t<auto, auto, auto> const& b){
		//auto constexpr operation_order=static_compare(a.operation,b.operation);
		//if constexpr(operation_order!=0) return operation_order;

		//auto first_order=static_compare(a.first,b.first);
		//if(first_order!=0) return first_order;

		//return static_compare(a.second, b.second);
	//}
	
	//indexed_element
	template<int i> struct indexed_element_t{
		static int constexpr index=i;
	};

	template<int i>
	bool constexpr operator==(indexed_element_t<i> const&, indexed_element_t<i> const&){
		return true;
	}
	template<int i>
	bool constexpr operator!=(indexed_element_t<i> const& a, indexed_element_t<i> const& b){
		return !(a==b);
	}

	template<int i>
	std::ostream& operator<<(std::ostream& out, indexed_element_t<i> const&){
		return out<<"e"<<i;
	}

	template<int ia, int ib>
	constexpr int static_compare(auto, indexed_element_t<ia> const&, indexed_element_t<ib> const&){return ib-ia;}

}

#endif /* GROUP_COMMUTATION_H */
