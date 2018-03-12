#ifndef SYMBOLIC_OPERATION_H
#define SYMBOLIC_OPERATION_H 

#include"../symbol.h"
#include"../../unit_test.h"
#include"../../scalar.h"
#include"../../group/operation.h"
#include<boost/hana.hpp>
#include<iostream>
#include<type_traits>

namespace symbolic{
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

	template<class> struct is_operation:std::false_type{};
	template<class OperationT, class... OperandsT>
	struct is_operation<operation_t<OperationT, OperandsT...>>:std::true_type{};
	template<class T> concept bool Operation=is_operation<T>::value;

	template<class OperationT, class... OperandsT>
	auto constexpr check_equal(operation_t<OperationT, OperandsT...> const& a, operation_t<OperationT, OperandsT...> const& b){
		using ::check_equal;
		std::cout<<"checking "<<a<<" equals "<<b<<" : ";
		return check_equal(a.operands, b.operands);
	}

	//ordering for commutation
	Operation{Operation2}
	constexpr int static_compare(Operation const& a, Operation2 const& b){return index(b.operation)-index(a.operation);}

	//formatting
	template<class OperationT, class... OperandsT>
	std::ostream& operator<<(std::ostream& out, operation_t<OperationT, OperandsT...> const& operation){
		out<<operation.operation<<"("<<boost::hana::front(operation.operands);
		boost::hana::for_each(boost::hana::drop_front(operation.operands), [&out](auto const& operand){out<<", "<<operand;});
		return out<<")";
	}
}

#endif /* SYMBOLIC_OPERATION_H */
