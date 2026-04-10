#ifndef SYMBOLIC_OPERATION_ALL_H
#define SYMBOLIC_OPERATION_ALL_H 

#include"template.h"
#include"../../group/morphism.h"
#include"../../addition/all.h"
#include"../../multiplication/all.h"
#include"../../differentiate.h"
#include"../../eval.h"

namespace godefv::math{
#define DEFINE_OPERATION(op, op_index, op_constraint) \
	struct op##_t{}; \
	inline std::ostream& operator<<(std::ostream& out, op##_t const){return out<<#op;} \
	template<class... OperandsT> requires op_constraint auto constexpr op(OperandsT const&... operands){return operation_t{op##_t{}, operands...};} \
	template<class T> auto constexpr eval_with_data(operation_t<op##_t, T> const& operand, auto const& eval_data){using std::op; return op(eval_with_data(operand.operand(), eval_data));} \
	std::intmax_t constexpr index(op##_t){return op_index;}
	DEFINE_OPERATION(exp  , 0, true)
	DEFINE_OPERATION(log  , 1, true)
	DEFINE_OPERATION(abs  , 2, true)
	DEFINE_OPERATION(cos  , 3, true)
	DEFINE_OPERATION(sin  , 4, false)
	DEFINE_OPERATION(tan  , 5, true)
	DEFINE_OPERATION(acos , 6, true)
	DEFINE_OPERATION(asin , 7, true)
	DEFINE_OPERATION(atan , 8, true)
	DEFINE_OPERATION(cosh , 9, true)
	DEFINE_OPERATION(sinh , 10, true)
	DEFINE_OPERATION(tanh , 11, true)
	DEFINE_OPERATION(acosh, 12, true)
	DEFINE_OPERATION(asinh, 13, true)
	DEFINE_OPERATION(atanh, 14, true)
#undef DEFINE_OPERATION

	//abs(x)=x if x>=0
	auto constexpr abs(PositiveScalar auto const & a){return a;}
	//abs(x)=-x if x<0
	template<class OperandT> requires (!PositiveScalar<OperandT> && PositiveScalar<decltype(-OperandT{})>)
	auto constexpr abs(OperandT a){return -a;}
	//abs is an endomorphism over *
	auto constexpr abs_endomorphism=group::endomorphism(mult_operation_t{}, [](auto const& a){return abs(a);});
	template<class T> requires (!PositiveScalar<T> && (group::Generated<T,add_operation_t> || group::Generated<T,mult_operation_t>))
	auto constexpr abs(T const& a){
		return abs_endomorphism(a);
	}
	//abs is not an endomorphism over + because abs(-x)!=-abs(x)
	template<class ExponentT, class X>
	auto constexpr abs(group::generated_power_t<add_operation_t,ExponentT,X> const& pow){
		return abs(pow.exponent)*abs(pow.operand);
	}
	template<class A, class B>
	auto constexpr abs(group::generated_by_operation_t<add_operation_t,A,B> const& ab){
		return abs(ab.first)+abs(ab.second);
	}
	auto constexpr abs(zero_t){
		return zero;
	}
	//abs(x)²=x²
	template<NonZeroInteger ExponentT> requires Integer<decltype(ExponentT{}/integer<2>)>
	auto constexpr generated_power(mult_operation_t, ExponentT exponent, operation_t<abs_t,Scalar auto> abs_x){
		return group::power(mult_operation_t{}, exponent, abs_x.operand());
	}
	//abs(x)>0
	template<class X>
	auto constexpr operator>=(operation_t<abs_t,X>, integer_t<0>){return std::true_type{};}

	//reverse
	template<class X>
	auto constexpr reverse(operation_t<exp_t,X> const& op){
		return exp(reverse(op.operand()));
	}

	//differentiate
	template<class Name, class X>
	auto constexpr differentiate(symbol_t<Name> variable, operation_t<exp_t,X> const& op){
		return differentiate(variable, op.operand())*op;
	}
	template<class Name, class X>
	auto constexpr differentiate(symbol_t<Name> variable, operation_t<log_t,X> const& op){
		return differentiate(variable, op.operand())/op.operand();
	}
	template<class Name, class X>
	auto constexpr differentiate(symbol_t<Name> variable, operation_t<cos_t,X> const& op){
		return -differentiate(variable, op.operand())*sin(op.operand());
	}
	template<class Name, class X>
	auto constexpr differentiate(symbol_t<Name> variable, operation_t<sin_t,X> const& op){
		return differentiate(variable, op.operand())*cos(op.operand());
	}
	template<class Name, class X>
	auto constexpr differentiate(symbol_t<Name> variable, operation_t<cosh_t,X> const& op){
		return differentiate(variable, op.operand())*sinh(op.operand());
	}
	template<class Name, class X>
	auto constexpr differentiate(symbol_t<Name> variable, operation_t<sinh_t,X> const& op){
		return differentiate(variable, op.operand())*cosh(op.operand());
	}
}

#endif /* SYMBOLIC_OPERATION_ALL_H */
