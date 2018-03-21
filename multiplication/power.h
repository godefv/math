#ifndef MULTIPLICATION_POWER_H
#define MULTIPLICATION_POWER_H 

#include"operation.h"
#include"../group/power.h"

namespace math{
	//exact roots
	template<std::intmax_t Exponent, std::intmax_t N, std::intmax_t left, std::intmax_t right>
	auto constexpr static_sqrt(integer_t<N> target, integer_t<left>, integer_t<right>){
		if constexpr(left == right){
			return group::power(mult_operation_t{}, ratio<1,Exponent>, target);
		} else {
			auto constexpr mid = integer<(right+left)/2>;
			auto constexpr power=group::power(mult_operation_t{}, integer<Exponent>, mid);

			if constexpr(power == target){
				return mid;
			}else if constexpr(power > target){
				return static_sqrt<Exponent>(target, integer<left>, mid);
			} else {
				return static_sqrt<Exponent>(target, mid+integer<1>, integer<right>);
			}
		}
	}
}

namespace math::group{	
	//power of integers
	template<Ratio RatioT, std::intmax_t N> requires RatioT::num==1 && RatioT::den>1 && N>1
	auto constexpr power(mult_operation_t, RatioT, integer_t<N> res){
		return static_sqrt<RatioT::den>(res, integer<1>, res);
	}
}

namespace math{
	//aliases
	template<Ratio RatioT, class OperandT>
	using power_t=group::generated_power_t<mult_operation_t, RatioT, OperandT>;

	template<Ratio RatioT, class OperandT>
	using nth_root_t=power_t<decltype(inverse(RatioT{})), OperandT>;

	template<class OperandT>
	using square_t=power_t<integer_t<2>, OperandT>;

	auto constexpr pow(auto const& operand, Ratio exponent){return group::power(mult_operation_t{}, exponent, operand);}
	template<std::intmax_t N>
	auto constexpr pow(auto const& operand){return pow(operand, integer<N>);}
	template<std::intmax_t N>
	auto constexpr nth_root(auto const& operand){return pow(operand, ratio<1,N>);}
	auto constexpr square(auto const& operand){return pow<2>(operand);}
	auto constexpr sqrt(auto const& operand){return nth_root<2>(operand);}

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
