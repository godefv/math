#ifndef SYMBOLIC_OPERATION_H
#define SYMBOLIC_OPERATION_H 

#include"../symbol.h"
#include"../../group/commutation.h"
#include"../../unit_test.h"
#include"../../scalar.h"

#include<boost/hana.hpp>
#include<iostream>
#include<type_traits>

namespace math{
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
	template<class T> concept bool Operation=is_operation<T>::value;

	//comparisons
	Operation{Operation2}
	auto constexpr operator==(Operation const& a, Operation2 const& b){
		return a.operands==b.operands;
	}
	Operation{OperationT}
	auto constexpr operator==(OperationT const& a, OperationT const& b){
		return a.operands==b.operands;
	}
	Operation{Operation2}
	auto constexpr operator!=(Operation const& a, Operation2 const& b){
		return !(a.operands==b.operands);
	}
	Operation{OperationT}
	auto constexpr check_equal(OperationT const& a, OperationT const& b){
		using ::check_equal;
		std::cout<<"checking "<<a<<" equals "<<b<<" : ";
		return check_equal(a.operands, b.operands);
	}

	//ordering for commutation
	Operation{Operation2}
	constexpr int static_compare(auto op, Operation const& a, Operation2 const& b){
		if(index(b.operation)==index(a.operation) && Symbol<decltype(a.operand())> && Symbol<decltype(b.operand())>){
			return static_compare(op, a.operand(),b.operand());
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
