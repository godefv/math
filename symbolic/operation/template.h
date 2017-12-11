#ifndef SYMBOLIC_OPERATION_H
#define SYMBOLIC_OPERATION_H 

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

	//mult operation
	struct mult_operation_t{
		//commutations rules
		template<class A,class B> 
			requires Operation<A>
			      && Operation<B>
			      && static_compare(A{},B{})<0
		static constexpr auto apply(A const& a, B const& b){
			return apply(b,a);
		}
		//group rules
		template<class A,class B> 
		static constexpr auto apply(A const& a, B const& b){
			return group::operation<mult_operation_t>(a,b);
		}
		vector::Scalar{Scalar2}
		static constexpr auto apply(vector::Scalar const& a, Scalar2 const& b){
			return a*b;
		}

		//group inverse
		template<class A>
		static constexpr auto inverse(A const& a){return group::inverse<mult_operation_t>(a);}
	};
	//operators
	Operation{Operation2}
	constexpr auto operator*(Operation const& a, Operation2 const& b){
		return mult_operation_t::apply(a,b);
	}

	//formatting
	template<class OperationT, class... OperandsT>
	std::ostream& operator<<(std::ostream& out, operation_t<OperationT, OperandsT...> const& operation){
		out<<operation.operation<<"("<<boost::hana::front(operation.operands);
		boost::hana::for_each(boost::hana::drop_front(operation.operands), [&out](auto const& operand){out<<", "<<operand;});
		return out<<")";
	}

	std::ostream& operator<<(std::ostream& out, group::generated_element_t<mult_operation_t, auto, auto> const& ab){
		return out<<"("<<ab.first<<") * ("<<ab.second<<")";
	}
}

#endif /* SYMBOLIC_OPERATION_H */
