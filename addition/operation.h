#ifndef ADDITION_OPERATION_H
#define ADDITION_OPERATION_H 

#include"../group/operation.h"
#include"../group/commutation.h"
#include"../group/power.h"
#include"../scalar.h"

#include<iostream>

//enable "using ::operator+;"
template<class A, class B> requires false
auto constexpr operator+(A,B);

namespace math{
	struct add_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a+b;
		}
	};
	//zero
	auto constexpr identity(add_operation_t){return integer<0>;}
	using zero_t=integer_t<0>;
	auto constexpr zero=zero_t{};

	//inverse
	template<class T> requires !group::Generated<add_operation_t,T>
	auto constexpr inverse(add_operation_t, T const& a){
		return -a;
	}

	//minus_t
	template<class T>
	using minus_t=group::generated_power_t<add_operation_t, integer_t<-1>, T>;

	//by default, use group operations
	auto constexpr operator-(auto const& a){
		return group::inverse(add_operation_t{}, a);
	}
	auto constexpr operator+(auto const& a, auto const& b){
		return group::operation(add_operation_t{},a,b);
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
	//collapse ka+klb as k(a+lb) if a+lb can be processed
	template<class A, class B, Symbol ExponentA, Symbol ExponentB> 
		requires !std::is_same<decltype(A{}+group::power(add_operation_t{}, ExponentB{}/ExponentA{}, B{}))
		                      ,group::generated_by_operation_t<add_operation_t,decltype(A{}),decltype(group::power(add_operation_t{}, ExponentB{}/ExponentA{}, B{}))>
							  >::value 
	auto constexpr operator+(group::generated_power_t<add_operation_t,ExponentA,A> const& ka, group::generated_power_t<add_operation_t,ExponentB,B> const& kb){
		return group::power(add_operation_t{}, ExponentA{}, ka.operand+group::power(add_operation_t{}, ExponentB{}/ExponentA{}, kb.operand));
	}

	//collapse ka+b as k(a+b/k) if a+b/k can be processed
	template<class A, class B, Symbol K> 
		requires !std::is_same<decltype(A{}+group::power(add_operation_t{}, integer<1>/K{}, B{}))
		                      ,group::generated_by_operation_t<add_operation_t,decltype(A{}),decltype(group::power(add_operation_t{}, integer<1>/K{}, B{}))>
							  >::value 
	auto constexpr operator+(group::generated_power_t<add_operation_t,K,A> const& ka, B const& b){
		return group::power(add_operation_t{}, ka.exponent, ka.operand+group::power(add_operation_t{}, integer<1>/ka.exponent, b));
	}

	//formatting
	std::ostream& operator<<(std::ostream& out, group::generated_by_operation_t<add_operation_t, auto, auto> const& ab){
		return out<<"("<<ab.first<<") + ("<<ab.second<<")";
	}

	std::ostream& operator<<(std::ostream& out, group::generated_power_t<add_operation_t, Scalar, auto> const& kx){
		return out<<kx.exponent<<"*("<<kx.operand<<")";
	}
	std::ostream& operator<<(std::ostream& out, minus_t<auto> const& kx){
		return out<<"-("<<kx.operand<<")";
	}

}

#endif /* ADDITION_OPERATION_H */
