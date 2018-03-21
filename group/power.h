#ifndef GROUP_POWER_H
#define GROUP_POWER_H 

#include"identity.h"
#include"../symbolic/rational.h"

namespace math::group{
	template<class OperatorT, Ratio RatioT, class OperandT>
	struct generated_power_t{
		OperatorT operator_;
		RatioT exponent;
		OperandT operand;
	};
	template<class OperatorT, Ratio RatioT, class OperandT>
	generated_power_t(OperatorT,RatioT,OperandT)->generated_power_t<OperatorT,RatioT,OperandT>;

	//comparison of powers
	template<class OperatorT, class OperandT>
	bool operator==(generated_power_t<OperatorT,Ratio, OperandT> const& a, generated_power_t<OperatorT,Ratio, OperandT> const& b){
		return a.exponent==b.exponent && a.operand==b.operand;
	}
	template<class OperatorT>
	bool operator==(generated_power_t<OperatorT,Ratio, auto> const&, generated_power_t<OperatorT,Ratio, auto> const&){
		return false;
	}
	template<class OperatorT>
	bool operator!=(generated_power_t<OperatorT,Ratio, auto> const& a, generated_power_t<OperatorT,Ratio, auto> const& b){
		return !(a==b);
	}

	//formatting
	std::ostream& operator<<(std::ostream& out, generated_power_t<auto, Ratio, auto> const& pow){
		return out<<typeid(pow.operator_).name()<<" "<<pow.exponent<<" th power ("<<pow.operand<<")";
	}

	//overloadable constructor. Typically, addition nth power of x equals n*x
	template<class OperatorT, Ratio RatioT, class OperandT>
	auto constexpr generated_power(auto op, Ratio exponent, auto const& operand){
		return generated_power_t{op,exponent,operand};
	}

	//default power function
	template<class OperatorT>
	auto constexpr power(OperatorT, Ratio exponent, auto const& operand){
		if constexpr(exponent==integer<0>){
			return identity_t<OperatorT>{};
		}else if constexpr(exponent==integer<1>){
			return operand;
		}else{
			return generated_power_t{OperatorT{},exponent,operand};
		}
	}
	//power of identity is identity
	template<class OperatorT, Ratio RatioT>
	auto constexpr power(OperatorT, RatioT, identity_t<OperatorT> const& identity){
		return identity;
	}
	//power of power is a power
	template<class OperatorT, Ratio RatioT>
	auto constexpr power(OperatorT op, RatioT ratio, generated_power_t<OperatorT,Ratio,auto> const& operand){
		return power(op, ratio*operand.exponent, operand.operand);
	} 
	//some powers can be processed immediatly
	template<class OperatorT, Ratio RatioT> requires RatioT::den==1 && RatioT::num>1
	auto constexpr power(OperatorT op, RatioT, Ratio const& operand){
		return OperatorT::apply(power(op, integer_t<RatioT::num-1>{}, operand), operand);
	}

	//inverse
	template<class OperatorT>
	auto constexpr inverse(OperatorT, generated_power_t<OperatorT,Ratio,auto> const& pow){
		return power(pow.operator_, -pow.exponent, pow.operand);
	}

	//concept
	template<class> struct is_power:std::false_type{};
	template<class OperatorT, Ratio RatioT, class OperandT> struct is_power<generated_power_t<OperatorT,RatioT, OperandT>>:std::true_type{};
	template<class OperatorT, class T> concept bool Power=is_power<T>::value;
}

#endif /* GROUP_POWER_H */