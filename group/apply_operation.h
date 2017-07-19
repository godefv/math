#ifndef APPLY_OPERATION_H
#define APPLY_OPERATION_H 

namespace group{
	template<class Operator, class A, class B> 
	constexpr auto apply_operation(A const& a, B const& b){return Operator::apply(a,b);}
}

#endif /* APPLY_OPERATION_H */
