#ifndef GROUP_POWER_H
#define GROUP_POWER_H 

#include"identity.h"
#include"../symbolic/rational.h"
#include"../scalar.h"

namespace math::group{
	template<class OperatorT, Scalar ExponentT, class OperandT>
	struct generated_power_t{
		OperatorT operator_;
		ExponentT exponent;
		OperandT operand;
	};
	template<class OperatorT, Scalar ExponentT, class OperandT>
	generated_power_t(OperatorT,ExponentT,OperandT)->generated_power_t<OperatorT,ExponentT,OperandT>;

	//comparison of powers
	template<class OperatorT, class OperandT>
	bool operator==(generated_power_t<OperatorT,Scalar, OperandT> const& a, generated_power_t<OperatorT,Scalar, OperandT> const& b){
		return a.exponent==b.exponent && a.operand==b.operand;
	}
	template<class OperatorT>
	bool operator==(generated_power_t<OperatorT,Scalar, auto> const&, generated_power_t<OperatorT,Scalar, auto> const&){
		return false;
	}
	template<class OperatorT>
	bool operator!=(generated_power_t<OperatorT,Scalar, auto> const& a, generated_power_t<OperatorT,Scalar, auto> const& b){
		return !(a==b);
	}

	//formatting
	std::ostream& operator<<(std::ostream& out, generated_power_t<auto, Scalar, auto> const& pow){
		return out<<typeid(pow.operator_).name()<<" "<<pow.exponent<<" th power ("<<pow.operand<<")";
	}

	//overloadable constructor. Typically, x**2=-1
	auto constexpr generated_power(auto op, auto exponent, auto const& operand){
		return generated_power_t{op,exponent,operand};
	}

	//default power function
	template<class OperandT>
	auto constexpr power(auto op, auto const& exponent, OperandT const& operand){
		return generated_power(op,exponent,operand);
	}
	//power of identity is identity
	template<class OperatorT> requires true //gives priority to this overload
	auto constexpr power(OperatorT, auto, identity_t<OperatorT> const& identity){
		return identity;
	}
	//special powers
	template<class OperatorT, class OperandT> requires !std::is_same<OperandT,identity_t<OperatorT>>::value
	auto constexpr power(OperatorT op, integer_t<0>, OperandT const&){
		return identity(op);
	}
	template<class OperatorT, class OperandT> requires !std::is_same<OperandT,identity_t<OperatorT>>::value
	auto constexpr power(OperatorT, integer_t<1>, OperandT const& operand){
		return operand;
	}
	//power of power is a power
	template<class OperatorT, Scalar ExponentT, Scalar ScalarT> 
		requires !std::is_same<ExponentT,integer_t<1>>::value
	auto constexpr power(OperatorT op, ExponentT ratio, generated_power_t<OperatorT,ScalarT,auto> const& operand){
		return power(op, ratio*operand.exponent, operand.operand);
	} 
	//some powers can be processed immediatly
	template<class OperatorT, Integer ExponentT, Ratio OperandT> requires ExponentT::num>1 && !std::is_same<OperandT,identity_t<OperatorT>>::value
	auto constexpr power(OperatorT op, ExponentT, OperandT const& operand){
		return OperatorT::apply(power(op, integer_t<ExponentT::num-1>{}, operand), operand);
	}
	//some operand are cyclic
	//template<class OperatorT> std::uintmax_t constexpr cycle_order(OperatorT,auto);
	template<class OperatorT, std::intmax_t Exponent, class OperandT> 
		requires !(0<=Exponent && Exponent<cycle_order(OperatorT{},OperandT{}))
	auto constexpr power(OperatorT op, integer_t<Exponent>, OperandT const& operand){
		auto constexpr order=cycle_order(OperatorT{},OperandT{});
		auto constexpr modulo=Exponent%order;
		auto constexpr reduced_exponent=(modulo<0)?modulo+order:modulo;
		return power(op, integer<reduced_exponent>, operand);
	}

	//inverse
	template<class OperatorT>
	auto constexpr inverse(OperatorT, generated_power_t<OperatorT,SimpleScalar,auto> const& pow){
		return power(pow.operator_, -pow.exponent, pow.operand);
	}

	//concept
	template<class OperatorT, class> struct is_power:std::false_type{};
	template<class OperatorT, Scalar ExponentT, class OperandT> struct is_power<OperatorT, generated_power_t<OperatorT,ExponentT, OperandT>>:std::true_type{};
	template<class OperatorT, class T> concept bool Power=is_power<OperatorT, T>::value;
}

namespace math{
	template<class OperatorT, Symbol ExponentT, Symbol SymbolT> struct is_symbol<group::generated_power_t<OperatorT,ExponentT,SymbolT>>:std::true_type{};
	template<class OperatorT, Scalar ExponentT, Scalar ScalarT> struct is_scalar<group::generated_power_t<OperatorT,ExponentT,ScalarT>>:std::true_type{};
}

#endif /* GROUP_POWER_H */
