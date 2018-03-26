#ifndef ADDITION_OPERATION_H
#define ADDITION_OPERATION_H 

#include"../group/operation.h"
#include"../group/commutation.h"
#include"../group/power.h"

#include<iostream>

namespace math{
	struct add_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a+b;
		}
	};
	using zero_t=group::identity_t<add_operation_t>;
	auto constexpr zero=zero_t{};

	template<class T> requires !group::Generated<add_operation_t,T>
	auto constexpr inverse(add_operation_t, T const& a){
		return -a;
	}

	//by default, use group operations
	auto constexpr operator-(auto const& a){
		return group::inverse(add_operation_t{}, a);
	}
	auto constexpr operator+(auto const& a, auto const& b){
		return group::operation<add_operation_t>(a,b);
	}
	auto constexpr operator-(auto const& a, auto const& b){
		return a+(-b);
	}

   	//commutation rule
   	template<class A, class B>
   		requires !std::is_same<A,B>::value 
		      && !group::Operation<add_operation_t,A>
		      && !group::Operation<add_operation_t,B>
   		      && static_compare(add_operation_t{}, A{},B{})<0
   	auto constexpr operator+(A const& a, B const& b){
   		return b+a;
   	}

	//formatting
	std::ostream& operator<<(std::ostream& out, group::generated_by_operation_t<add_operation_t, auto, auto> const& ab){
		return out<<"("<<ab.first<<") + ("<<ab.second<<")";
	}

	std::ostream& operator<<(std::ostream& out, group::generated_power_t<add_operation_t, Ratio, auto> const& kx){
		return out<<kx.exponent<<"*("<<kx.operand<<")";
	}
	std::ostream& operator<<(std::ostream& out, group::generated_power_t<add_operation_t, integer_t<-1>, auto> const& kx){
		return out<<"-("<<kx.operand<<")";
	}

}

#endif /* ADDITION_OPERATION_H */
