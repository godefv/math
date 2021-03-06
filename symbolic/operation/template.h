#ifndef SYMBOLIC_OPERATION_H
#define SYMBOLIC_OPERATION_H 

#include"../symbol.h"
#include"../../group/commutation.h"
#include"../../unit_test.h"
#include"../../scalar.h"

#include<boost/hana.hpp>
#include<iostream>
#include<type_traits>
#include<concepts>

namespace godefv::math{
	template<class OperationT, class... OperandsT>
	struct operation_t{
		OperationT operation; 
		boost::hana::tuple<OperandsT...> operands;

		constexpr operation_t()=default;
		constexpr operation_t(OperationT const& operation_in, OperandsT const&... operands_in)
			:operation{operation_in}, operands{boost::hana::make_tuple(operands_in...)}
		{}

		auto constexpr operand() const{
			return boost::hana::front(operands);
		}
	};

	template<class OperationT, Symbol... OperandsT>
	struct is_symbol<operation_t<OperationT, OperandsT...>>: std::true_type{};

	template<class OperationT, Scalar ScalarT> 
	struct is_scalar<operation_t<OperationT,ScalarT>>:std::true_type{};

	//concept
	template<class> struct is_operation:std::false_type{};
	template<class OperationT, class... OperandsT>
	struct is_operation<operation_t<OperationT, OperandsT...>>:std::true_type{};
	template<class T> concept Operation=is_operation<T>::value;

	//comparisons
	auto constexpr operator==(Operation auto const& a, Operation auto const& b){
		return std::same_as<decltype(a.operation), decltype(b.operation)> && a.operands==b.operands;
	}
	auto constexpr operator!=(Operation auto const& a, Operation auto const& b){
		return !(a.operands==b.operands);
	}
	template<Operation OperationT>
	auto constexpr check_equal(OperationT const& a, OperationT const& b){
		using ::check_equal;
		std::cout<<"checking "<<a<<" equals "<<b<<" : ";
		return check_equal(a.operands, b.operands);
	}

	//ordering for commutation
	auto constexpr sort_operation_operand_as(auto, auto const& a){return a;}
	constexpr int static_compare(auto op, Operation auto const& a, Operation auto const& b){
		if(index(b.operation)==index(a.operation)){
			return static_compare(op
				,sort_operation_operand_as(a.operation, a.operand())
				,sort_operation_operand_as(b.operation, b.operand())
			);
		}else{
			return index(b.operation)-index(a.operation);
		}
	}

	//formatting
	template<class OperationT, class... OperandsT>
	std::ostream& operator<<(std::ostream& out, operation_t<OperationT, OperandsT...> const& operation){
		out<<operation.operation<<"("<<boost::hana::front(operation.operands);
		boost::hana::for_each(boost::hana::drop_front(operation.operands), [&out](auto const& operand){out<<", "<<operand;});
		return out<<")";
	}
}


#endif /* SYMBOLIC_OPERATION_H */
