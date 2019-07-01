#ifndef SYMBOLIC_OPERATION_ALL_H
#define SYMBOLIC_OPERATION_ALL_H 

#include"template.h"
#include"../../group/morphism.h"
#include"../../addition/all.h"
#include"../../multiplication/all.h"

namespace godefv::math{
#define DEFINE_OPERATION(op, op_index, op_constraint) \
	struct op##_t{}; \
	inline std::ostream& operator<<(std::ostream& out, op##_t const){return out<<#op;} \
	template<class... OperandsT> requires op_constraint auto constexpr op(OperandsT const&... operands){return operation_t{op##_t{}, operands...};} \
	auto constexpr eval_with_data(operation_t<op##_t, auto> const& operand, auto const& eval_data){using std::op; return op(eval_with_data(operand.operand(), eval_data));} \
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

	//abs is an endomorphism over *
	auto constexpr abs_endomorphism=group::endomorphism(mult_operation_t{}, [](auto const& a){return abs(a);});
	template<class T> requires group::Generated<add_operation_t,T> || group::Generated<mult_operation_t,T>
	auto constexpr abs(T const& a){
		return abs_endomorphism(a);
	}
	//abs is not an endomorphism over + because abs(-x)!=-abs(x)
	auto constexpr abs(group::generated_power_t<add_operation_t,auto,auto> const& pow){
		return abs(pow.exponent)*abs(pow.operand);
	}
	auto constexpr abs(group::generated_by_operation_t<add_operation_t,auto,auto> const& ab){
		return abs(ab.first)+abs(ab.second);
	}
	auto constexpr abs(zero_t){
		return zero;
	}

	//reverse
	constexpr auto reverse(operation_t<exp_t,auto> const& op){
		return exp(reverse(op.operand()));
	}
}

#endif /* SYMBOLIC_OPERATION_ALL_H */
