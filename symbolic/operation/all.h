#ifndef SYMBOLIC_OPERATION_ALL_H
#define SYMBOLIC_OPERATION_ALL_H 

#include"template.h"
#include"pow.h"
#include"../../eval.h"

namespace symbolic{
#define DEFINE_OPERATION(op) \
	struct op##_t{}; \
	inline std::ostream& operator<<(std::ostream& out, op##_t const){return out<<#op;} \
	template<class... OperandsT> auto constexpr op(OperandsT const&... operands){return operation_t{op##_t{}, operands...};} \
	auto constexpr eval(operation_t<op##_t, auto> const& operand){using std::op; return op(eval(operand.operand()));}
	DEFINE_OPERATION(exp)
	DEFINE_OPERATION(log)
	DEFINE_OPERATION(abs)
	DEFINE_OPERATION(sin)
	DEFINE_OPERATION(asin)
	DEFINE_OPERATION(sinh)
	DEFINE_OPERATION(asinh)
	DEFINE_OPERATION(cos)
	DEFINE_OPERATION(acos)
	DEFINE_OPERATION(cosh)
	DEFINE_OPERATION(acosh)
#undef DEFINE_OPERATION

	//inverse
	struct inverse_t{};
	inline std::ostream& operator<<(std::ostream& out, inverse_t const){return out<<"inverse";} 
	auto constexpr inverse(auto const& operand){return operation_t{inverse_t{}, operand};} 
	
	Symbol{SymbolT}
	auto constexpr operator*(operation_t<inverse_t,SymbolT>, SymbolT){return integer<1>;} 
	Symbol{SymbolT}
	auto constexpr operator*(SymbolT, operation_t<inverse_t,SymbolT>){return integer<1>;} 

	auto constexpr eval(operation_t<inverse_t, auto> const& operand){
		auto evaluated_operand=eval(operand.operand());
		if constexpr(std::is_same<decltype(evaluated_operand), double>::value){
			return 1./evaluated_operand;
		}else{
			return inverse(evaluated_operand);
		}
	}

	//minus
	struct minus_t{}; 
	inline std::ostream& operator<<(std::ostream& out, minus_t const){return out<<"minus";} 
	namespace operators{ 
	auto constexpr operator-(auto const& a){return operation_t{minus_t{}, a};} 
	} 
	auto constexpr eval(operation_t<minus_t, auto> const& operand){
		auto evaluated_operand=eval(operand.operand());
		if constexpr(std::is_same<decltype(evaluated_operand), double>::value){
			return -evaluated_operand;
		}else{
			return inverse(evaluated_operand);
		}
	}

	//pow is put outer not to interfere with inner simplifications
	template<Ratio RatioT>
	auto constexpr inverse(operation_t<pow_t<RatioT>,auto> const& operand){
		return pow<RatioT>(inverse(operand.operand()));
	} 
	//abs is put outer not to interfere with inner simplifications
	auto constexpr inverse(operation_t<abs_t,auto> const& operand){
		return abs(inverse(operand.operand()));
	} 
	//abs is put outer not to interfere with inner simplifications
	template<Ratio RatioT>
	auto constexpr pow(operation_t<abs_t,auto> const& operation){
		return abs(pow<RatioT>(operation.operand()));
	} 
	
}

#endif /* SYMBOLIC_OPERATION_ALL_H */
