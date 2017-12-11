#ifndef SYMBOLIC_OPERATION_ALL_H
#define SYMBOLIC_OPERATION_ALL_H 

#include"template.h"
#include"pow.h"
#include"../../eval.h"

namespace symbolic{
#define DEFINE_OPERATION(op, op_index) \
	struct op##_t{}; \
	inline std::ostream& operator<<(std::ostream& out, op##_t const){return out<<#op;} \
	template<class... OperandsT> auto constexpr op(OperandsT const&... operands){return operation_t{op##_t{}, operands...};} \
	auto constexpr eval(operation_t<op##_t, auto> const& operand){using std::op; return op(eval(operand.operand()));} \
	std::intmax_t constexpr index(op##_t){return op_index;}
	DEFINE_OPERATION(exp  , 0)
	DEFINE_OPERATION(log  , 1)
	DEFINE_OPERATION(abs  , 2)
	DEFINE_OPERATION(sin  , 3)
	DEFINE_OPERATION(asin , 4)
	DEFINE_OPERATION(sinh , 5)
	DEFINE_OPERATION(asinh, 6)
	DEFINE_OPERATION(cos  , 7)
	DEFINE_OPERATION(acos , 8)
	DEFINE_OPERATION(cosh , 9)
	DEFINE_OPERATION(acosh, 10)
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
