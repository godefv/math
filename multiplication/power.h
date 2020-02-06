#ifndef MULTIPLICATION_POWER_H
#define MULTIPLICATION_POWER_H 

#include"operation.h"
#include"commutator.h"
#include"../group/power.h"

#include<cmath>

namespace godefv::math{
	//aliases
	template<SimpleScalar ExponentT, class OperandT>
	using power_t=group::generated_power_t<mult_operation_t, ExponentT, OperandT>;

	template<Ratio RatioT, class OperandT>
	using nth_root_t=power_t<decltype(inverse(RatioT{})), OperandT>;

	template<class OperandT>
	using square_t=power_t<integer_t<2>, OperandT>;

	template<class OperandT>
	using sqrt_t=nth_root_t<integer_t<2>, OperandT>;

	auto constexpr pow(auto const& operand, Ratio exponent){
		using group::power;
		return power(mult_operation_t{}, exponent, operand);
	}
	template<std::intmax_t N>
	auto constexpr pow(auto const& operand){return pow(operand, integer<N>);}
	template<std::intmax_t N>
	auto constexpr nth_root(auto const& operand){return pow(operand, ratio<1,N>);}
	auto constexpr square(auto const& operand){return pow<2>(operand);}
	auto constexpr sqrt(auto const& operand){return nth_root<2>(operand);}

	//static square root function for integers
	template<Integer Integer1, Integer Integer2>
	auto constexpr static_sqrt_linear(one_t,Integer1,Integer2){
		return integer<1>;
	}
	template<Integer Integer1, Integer Integer2>
	auto constexpr static_sqrt_linear(Integer operand, Integer1 exponent, Integer2 i){
		auto constexpr power=group::power(mult_operation_t{}, exponent, i);
		auto constexpr ratio=operand/power;
		if constexpr(ratio.denominator()==1){
			return i*group::power(mult_operation_t{}, inverse(exponent), ratio);
		}else if constexpr(power<operand){
			return static_sqrt_linear(operand, exponent, i+integer<1>);
		}else{
			return group::generated_power(mult_operation_t{}, inverse(exponent), operand);
		}
	}
	template<std::intmax_t Exponent>
	auto constexpr static_sqrt(Integer operand){
		return static_sqrt_linear(operand, integer<Exponent>, integer<2>);
	}

	//exact roots of rationals
	template<SimpleScalar ExponentT, Ratio RatioT> requires ExponentT::num==1 && ExponentT::den>1 && RatioT::num>0 && !std::is_same<RatioT,integer_t<1>>::value
	auto constexpr generated_power(mult_operation_t, ExponentT, RatioT){
		return static_sqrt<ExponentT::den>(integer<RatioT::num>)/static_sqrt<ExponentT::den>(integer<RatioT::den>);
	}
	//apply inverse if different than power<-1> (only with rational operands for now, because we know they can then be processed immediately)
	template<SimpleScalar ExponentT, Ratio OperandT> requires ExponentT::num<0 && !(Integer<OperandT> && !Integer<ExponentT>)
	auto constexpr generated_power(mult_operation_t, ExponentT exponent, OperandT const& operand){
		return group::power(mult_operation_t{}, -exponent, inverse(operand));
	}
	//power of addition powers (ka)^n = (k^n)(a^n) because k is a scalar
	template<Scalar Exponent1, Scalar Exponent2>
	auto constexpr generated_power(mult_operation_t, Exponent1 exponent, group::generated_power_t<add_operation_t, Exponent2, auto> const& pow_ab){
		using group::power;
		return power(add_operation_t{}, power(mult_operation_t{}, exponent, pow_ab.exponent), power(mult_operation_t{}, exponent, pow_ab.operand));
	}
	//power of multiplication with a scalar (ka)^n = (k^n)(a^n) because k is a scalar
	//typically, multiplicaation with sqrt(2) or pi are kept as multiplication, not addition power
	template<Scalar Exponent1, class A, class B> requires Scalar<A> || Scalar<B>
	auto constexpr generated_power(mult_operation_t, Exponent1 exponent, group::generated_by_operation_t<mult_operation_t, A, B> const& ab){
		using group::power;
		return power(mult_operation_t{}, exponent, ab.first)*power(mult_operation_t{}, exponent, ab.second);
	}
	//expand powers of multiplication or addition a^n = a(a^(n-1)) with a=xy or x+y 
	//this gives a chance to apply commutation rules, and expands (a+b)^n
	template<SimpleScalar ExponentT, class T> 
		requires ExponentT::num>0 
		      && ExponentT::den==1 
			  && (group::Operation<T,mult_operation_t> || group::Operation<T,add_operation_t>)
	auto constexpr generated_power(mult_operation_t, ExponentT exponent, T const& a){
		return a*group::power(mult_operation_t{}, exponent-integer<1>, a);
	}
	//(ka+lb)² =(ka)²+(lb)²+(kl)(ab+ba), factoring (kl) gives a chance to simplify (ab+ba), which is not always possible if (kl) is a runtime value
	auto constexpr generated_power(mult_operation_t, integer_t<2>, group::generated_by_operation_t<add_operation_t, auto, auto> const& ka_plus_lb){
		return square(ka_plus_lb.first)+square(ka_plus_lb.second)+anticommutator(ka_plus_lb.first, ka_plus_lb.second);
	}
	//powers of runtime values
	auto constexpr generated_power(mult_operation_t, SimpleScalar const& exponent, Number const& operand){
		return std::pow(operand, eval(exponent));
	}

	//eval
	auto constexpr eval_with_data(group::generated_power_t<mult_operation_t,auto,auto> const& pow, auto const& eval_data){
		return std::pow(eval_with_data(pow.operand, eval_data), eval_with_data(pow.exponent, eval_data));
	}

	//formatting
	inline std::ostream& operator<<(std::ostream& out, power_t<SimpleScalar,auto> const& pow){return out<<pow.exponent<<" th power("<<pow.operand<<")";}

	using namespace std::string_view_literals;
	std::string_view constexpr exponent_string(integer_t<2>){return "²"sv;}
	std::string_view constexpr exponent_string(integer_t<3>){return "³"sv;}
	std::string_view constexpr exponent_string(integer_t<4>){return "⁴"sv;}
	template<SimpleScalar ExponentT> requires requires(){exponent_string(ExponentT{});}
	inline std::ostream& operator<<(std::ostream& out, power_t<ExponentT, auto> const& pow){
		return out<<"("<<pow.operand<<")"<<exponent_string(pow.exponent);
	}
	template<SimpleScalar ExponentT> requires !requires(){exponent_string(ExponentT{});} && requires(){exponent_string(inverse(ExponentT{}));} 
	inline std::ostream& operator<<(std::ostream& out, power_t<ExponentT, auto> const& pow){
		return out<<exponent_string(inverse(pow.exponent))<<"√("<<pow.operand<<")";
	}
}

#endif /* MULTIPLICATION_POWER_H */
