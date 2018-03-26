#ifndef GROUP_MORPHISM_H
#define GROUP_MORPHISM_H 

#include"operation.h"

namespace math::group{
	template<class InnerOperatorT, class OuterOperatorT, class FunctorT>
	struct morphism_t{
		InnerOperatorT inner_operator;
		OuterOperatorT outer_operator;
		FunctorT f;

		auto constexpr operator()(auto const& a){
			return f(a);
		}
		auto constexpr operator()(generated_by_operation_t<InnerOperatorT, auto,auto> const& ab){
			return OuterOperatorT::apply(operator()(ab.first),operator()(ab.second));
		}
		auto constexpr operator()(generated_power_t<InnerOperatorT, Ratio, auto> const& pow){
			return group::power(outer_operator, pow.exponent, operator()(pow.operand));
		}
		auto constexpr operator()(identity_t<InnerOperatorT>){
			return identity_t<OuterOperatorT>{};
		}
	};
	template<class InnerOperatorT, class OuterOperatorT, class FunctorT>
	morphism_t(InnerOperatorT,OuterOperatorT,FunctorT)->morphism_t<InnerOperatorT,OuterOperatorT,FunctorT>;

	template<class OperatorT, class FunctorT>
	using endomorphism_t=morphism_t<OperatorT, OperatorT, FunctorT>;

	template<class OperatorT, class FunctorT>
	auto constexpr endomorphism(OperatorT op, FunctorT const& f){return morphism_t{op, op, f};}
}

#endif /* GROUP_MORPHISM_H */
