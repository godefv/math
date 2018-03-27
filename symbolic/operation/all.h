#ifndef SYMBOLIC_OPERATION_ALL_H
#define SYMBOLIC_OPERATION_ALL_H 

#include"template.h"
#include"../../group/morphism.h"
#include"../../addition/all.h"
#include"../../multiplication/all.h"

namespace math{
#define DEFINE_OPERATION(op, op_index) \
	struct op##_t{}; \
	inline std::ostream& operator<<(std::ostream& out, op##_t const){return out<<#op;} \
	template<class... OperandsT> auto constexpr op(OperandsT const&... operands){return operation_t{op##_t{}, operands...};} \
	auto constexpr eval(operation_t<op##_t, auto> const& operand){using std::op; return op(eval(operand.operand()));} \
	std::intmax_t constexpr index(op##_t){return op_index;}
	DEFINE_OPERATION(exp  , 0)
	DEFINE_OPERATION(log  , 1)
	DEFINE_OPERATION(abs  , 2)
	DEFINE_OPERATION(cos  , 3)
	DEFINE_OPERATION(sin  , 4)
	DEFINE_OPERATION(acos , 5)
	DEFINE_OPERATION(asin , 6)
	DEFINE_OPERATION(cosh , 7)
	DEFINE_OPERATION(sinh , 8)
	DEFINE_OPERATION(acosh, 9)
	DEFINE_OPERATION(asinh, 10)
#undef DEFINE_OPERATION

	//abs is an endomorphism over the algebra(+,*)
	auto constexpr abs_endomorphism=group::endomorphism(add_operation_t{}, group::endomorphism(mult_operation_t{}, [](auto const& a){return abs(a);}));
	template<class T> requires group::Generated<add_operation_t,T> || group::Generated<mult_operation_t,T>
	auto constexpr abs(T const& a){
		return abs_endomorphism(a);
	}
}

#endif /* SYMBOLIC_OPERATION_ALL_H */
