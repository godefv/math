#ifndef SYMBOLIC_OPERATION_POW_H
#define SYMBOLIC_OPERATION_POW_H 

#include"template.h"
#include"../rational.h"
#include"../symbol.h"
#include"../../eval.h"
#include<cmath>

namespace symbolic{
	template<Ratio RatioT>
	struct pow_t{RatioT exponent;};
	template<Ratio RatioT>
	using nth_root_t=pow_t<decltype(inverse(RatioT{}))>;

	inline std::ostream& operator<<(std::ostream& out, pow_t<auto> const power_operation){return out<<"power<"<<power_operation.exponent<<">";}
	template<std::intmax_t N>
	inline std::ostream& operator<<(std::ostream& out, pow_t<integer_t<N>> const){return out<<N<<"th_power";}
	inline std::ostream& operator<<(std::ostream& out, pow_t<integer_t<2>> const){return out<<"square";}
	inline std::ostream& operator<<(std::ostream& out, pow_t<integer_t<3>> const){return out<<"cube";}
	template<std::intmax_t N>
	inline std::ostream& operator<<(std::ostream& out, pow_t<ratio_t<1,N>> const){return out<<N<<"th_root";}
	inline std::ostream& operator<<(std::ostream& out, nth_root_t<integer_t<2>> const){return out<<"sqrt";}
	inline std::ostream& operator<<(std::ostream& out, nth_root_t<integer_t<3>> const){return out<<"cubic_root";}

	using namespace std::string_view_literals;
	std::string_view constexpr exponent_string(integer_t<2>){return "²"sv;}
	std::string_view constexpr exponent_string(integer_t<3>){return "³"sv;}
	std::string_view constexpr exponent_string(integer_t<4>){return "⁴"sv;}
	template<Ratio RatioT> requires requires(){exponent_string(RatioT{});}
	inline std::ostream& operator<<(std::ostream& out, operation_t<pow_t<RatioT>, auto> const& operation){
		return out<<"("<<operation.operand()<<")"<<exponent_string(RatioT{});
	}
	template<Ratio RatioT> requires !requires(){exponent_string(RatioT{});} && requires(){exponent_string(inverse(RatioT{}));} 
	inline std::ostream& operator<<(std::ostream& out, operation_t<pow_t<RatioT>, auto> const& operation){
		return out<<exponent_string(inverse(RatioT{}))<<"√("<<operation.operand()<<")";
	}
	
	template<class Operands>
	bool operator==(operation_t<pow_t<Ratio>, Operands> const& a, operation_t<pow_t<Ratio>, Operands> const& b){
		return a.operation.exponent==b.operation.exponent && a.operands==b.operands;
	}
	bool operator==(operation_t<pow_t<Ratio>, auto> const& a, operation_t<pow_t<Ratio>, auto> const& b){
		return false;
	}
	bool operator!=(operation_t<pow_t<Ratio>, auto> const& a, operation_t<pow_t<Ratio>, auto> const& b){
		return !(a==b);
	}

	template<Ratio RatioT>
	auto constexpr pow(auto const& operand){
		if constexpr(std::is_same<RatioT,integer_t<1>>::value){
			return operand;
		}else{
			return operation_t{pow_t<RatioT>{}, operand};
		}
	}
	//power of power is a power
	template<Ratio RatioT>
	auto constexpr pow(operation_t<pow_t<Ratio>,auto> const& operation){
		return pow<decltype(RatioT{}*operation.operation.exponent)>(operation.operand());
	} 

	//pow() aliases
	template<std::intmax_t N>
	auto constexpr pow(auto const& operand){return pow<integer_t<N>>(operand);}
	template<std::intmax_t N>
	auto constexpr nth_root(auto const& operand){return pow<ratio_t<1,N>>(operand);}
	auto constexpr square(auto const& operand){return pow<2>(operand);}
	auto constexpr sqrt(auto const& operand){return nth_root<2>(operand);}

	auto constexpr eval(operation_t<pow_t<Ratio>, auto> const& operation){
		using std::pow; 
		using ::eval;
		return pow(eval(operation.operand()), eval(operation.operation.exponent));
	}
	auto constexpr eval(operation_t<nth_root_t<integer_t<2>>, auto> const& operation){
		using std::sqrt; 
		using ::eval;
		return sqrt(eval(operation.operand()));
	}

	template<Ratio RatioT>
	auto constexpr operator*(operation_t<pow_t<RatioT>, auto> const& a, operation_t<pow_t<RatioT>, auto> const& b){
		return operation_t{pow_t<RatioT>{}, a.operand()*b.operand()};
	}

	template<class Name>
	auto constexpr operator*(symbol_t<Name>,symbol_t<Name>){
		return operation_t{pow_t<integer_t<2>>{}, symbol_t<Name>{}};
	}

}

#endif /* SYMBOLIC_OPERATION_POW_H */
