#ifndef MULTIPLICATION_POWER_H
#define MULTIPLICATION_POWER_H 

#include"operation.h"
#include"../group/power.h"

#include<cmath>

namespace math{
	//static square root function for integers
	template<std::intmax_t Exponent, std::intmax_t N, std::intmax_t begin, std::intmax_t end>
	auto constexpr static_sqrt(integer_t<N> operand, integer_t<begin>, integer_t<end>){
		static_assert(begin<=end);
		//while range is not empty, search it by dichotomy
		if constexpr(begin!=end){
			auto constexpr mid = integer<(end+begin)/2>;
			auto constexpr power=group::power(mult_operation_t{}, integer<Exponent>, mid);

			if constexpr(power==operand){
				return mid;
			}else if constexpr(power>operand){
				return static_sqrt<Exponent>(operand, integer<begin>, mid);
			}else{
				return static_sqrt<Exponent>(operand, mid+integer<1>, integer<end>);
			}
		//if range is empty, no exact root has been found, so generate a symbolic power
		}else{
			return group::generated_power(mult_operation_t{}, ratio<1,Exponent>, operand);
		}
	}
	//exact roots of rationals
	template<Ratio RatioT, std::intmax_t N> requires RatioT::num==1 && RatioT::den>1 && N>1
	auto constexpr generated_power(mult_operation_t, RatioT, integer_t<N> operand){
		return static_sqrt<RatioT::den>(operand, integer<1>, operand);
	}
	//apply inverse if different than power<-1> (only with rational operands for now)
	template<class OperatorT, Ratio RatioT> requires RatioT::num<0
	auto constexpr generated_power(OperatorT op, RatioT exponent, Ratio const& operand){
		return group::power(op, -exponent, inverse(operand));
	}
	//power of addition powers (ka)^n = (k^n)(a^n) because k is a scalar
	template<Ratio Ratio1, Ratio Ratio2>
	auto constexpr generated_power(mult_operation_t, Ratio1 exponent, group::generated_power_t<add_operation_t, Ratio2, auto> const& pow_ab){
		using group::power;
		return power(add_operation_t{}, power(mult_operation_t{}, exponent, pow_ab.exponent), power(mult_operation_t{}, exponent, pow_ab.operand));
	}

	//aliases
	template<Ratio RatioT, class OperandT>
	using power_t=group::generated_power_t<mult_operation_t, RatioT, OperandT>;

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

	//eval
	auto constexpr eval(group::generated_power_t<mult_operation_t,auto,auto> const& pow){
		return std::pow(eval(pow.operand), eval(pow.exponent));
	}

	//formatting
	inline std::ostream& operator<<(std::ostream& out, power_t<Ratio,auto> const& pow){return out<<pow.exponent<<" th power("<<pow.operand<<")";}

	using namespace std::string_view_literals;
	std::string_view constexpr exponent_string(integer_t<2>){return "²"sv;}
	std::string_view constexpr exponent_string(integer_t<3>){return "³"sv;}
	std::string_view constexpr exponent_string(integer_t<4>){return "⁴"sv;}
	template<Ratio RatioT> requires requires(){exponent_string(RatioT{});}
	inline std::ostream& operator<<(std::ostream& out, power_t<RatioT, auto> const& pow){
		return out<<"("<<pow.operand<<")"<<exponent_string(pow.exponent);
	}
	template<Ratio RatioT> requires !requires(){exponent_string(RatioT{});} && requires(){exponent_string(inverse(RatioT{}));} 
	inline std::ostream& operator<<(std::ostream& out, power_t<RatioT, auto> const& pow){
		return out<<exponent_string(inverse(pow.exponent))<<"√("<<pow.operand<<")";
	}
}

#endif /* MULTIPLICATION_POWER_H */
