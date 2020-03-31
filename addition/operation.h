#ifndef ADDITION_OPERATION_H
#define ADDITION_OPERATION_H 

#include"../group/operation.h"
#include"../group/commutation.h"
#include"../group/power.h"
#include"../expression.h"
#include"../scalar.h"

#include<iostream>
#include<type_traits>

//enable "using ::operator+;"
template<class A, class B> requires false
auto constexpr operator+(A,B);

namespace godefv::math{
	struct add_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a+b;
		}
		auto constexpr operator()(auto const& a, auto const& b) const{
			return std::decay_t<decltype(*this)>::apply(a,b);
		}
	};
	//zero
	auto constexpr identity(add_operation_t){return integer<0>;}
	using zero_t=integer_t<0>;
	auto constexpr zero=zero_t{};

	//inverse
	template<class T> requires !group::Generated<T,add_operation_t>
	auto constexpr inverse(add_operation_t, T const& a){
		return -a;
	}

	//minus_t
	template<class T>
	using minus_t=group::generated_power_t<add_operation_t, integer_t<-1>, T>;

	//by default, use group operations
	auto constexpr operator-(NonSimpleScalarExpression const& a){
		return group::inverse(add_operation_t{}, a);
	}
   	template<Expression A, Expression B> requires !(
		   (Number<A> && Number<B>) //built-in
		|| (Number<A> && NonZeroRatio<B>) //defined in symbolic/rational.h
		|| (NonZeroRatio<A> && Number<B>) //defined in symbolic/rational.h
		|| (Ratio<A> && Ratio<B>) //defined in symbolic/rational.h
	)
	auto constexpr operator+(A const& a, B const& b){
		return group::operation(add_operation_t{},a,b);
	}
   	template<Expression A, Expression B> requires !(SimpleScalar<A> && SimpleScalar<B>)
	auto constexpr operator-(A const& a, B const& b){
		return a+(-b);
	}

   	//commutation rule
   	template<Expression A, Expression B>
   		requires !(
			  	(Number<A> && Number<B>) //built-in
			  	|| (Number<A> && NonZeroRatio<B>) //defined in symbolic/rational.h
			  	|| (NonZeroRatio<A> && Number<B>) //defined in symbolic/rational.h
			  	|| (Ratio<A> && Ratio<B>) //defined in symbolic/rational.h
			  )
		      && !std::is_same<A,B>::value 
		      && !group::Operation<A,add_operation_t>
		      && !group::Operation<B,add_operation_t>
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
	template<class A, Expression B, Symbol K> 
		requires !std::is_same<decltype(A{}+group::power(add_operation_t{}, integer<1>/K{}, B{}))
		                      ,group::generated_by_operation_t<add_operation_t,decltype(A{}),decltype(group::power(add_operation_t{}, integer<1>/K{}, B{}))>
							  >::value 
	auto constexpr operator+(group::generated_power_t<add_operation_t,K,A> const& ka, B const& b){
		return group::power(add_operation_t{}, ka.exponent, ka.operand+group::power(add_operation_t{}, integer<1>/ka.exponent, b));
	}

	//a+b>=0 if a,b>=0
	template<PositiveScalar A, PositiveScalar B>
	auto constexpr operator>=(group::generated_by_operation_t<add_operation_t,A,B>, zero_t){return std::true_type{};}
	//ka>=0 if k,a>=0
	template<PositiveScalar K, PositiveScalar A>
	auto constexpr operator>=(group::generated_power_t<add_operation_t,K,A>, zero_t){return std::true_type{};}

	//formatting
	namespace detail{
		template<class T> requires !group::Generated<T,add_operation_t>
		std::ostream& format_addition_left_operand(std::ostream& out, T const& operand){
			return out<<"("<<operand<<")";
		}
		std::ostream& format_addition_left_operand(std::ostream& out, group::Generated<add_operation_t> const& operand){
			return out<<operand;
		}
		std::ostream& format_addition_right_operand(std::ostream& out, auto const& operand){
			return out<<" + ("<<operand<<")";
		}
		std::ostream& format_addition_right_operand(std::ostream& out, minus_t<auto> const& operand){
			return out<<" - ("<<operand.operand<<")";
		}
		std::ostream& format_addition_right_operand(std::ostream& out, group::generated_power_t<add_operation_t, Scalar, auto> const& operand){
			return out<<" + "<<operand;
		}
	}
	std::ostream& operator<<(std::ostream& out, group::generated_by_operation_t<add_operation_t, auto, auto> const& ab){
		detail::format_addition_left_operand(out, ab.first);
		detail::format_addition_right_operand(out, ab.second);
		return out;
	}

	std::ostream& operator<<(std::ostream& out, group::generated_power_t<add_operation_t, Scalar, auto> const& kx){
		return out<<kx.exponent<<"*("<<kx.operand<<")";
	}
	std::ostream& operator<<(std::ostream& out, minus_t<auto> const& kx){
		return out<<"-("<<kx.operand<<")";
	}

}

#endif /* ADDITION_OPERATION_H */
