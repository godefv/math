#ifndef GROUP_MORPHISM_H
#define GROUP_MORPHISM_H 

#include"operation.h"

namespace math::group{
	template<class InnerOperatorT, class OuterOperatorT, class FunctorT>
	struct morphism_t{
		InnerOperatorT inner_operator;
		OuterOperatorT outer_operator;
		FunctorT f;

		template<class... ArgsT> auto constexpr operator()(auto const& a, ArgsT&&... args) const{
			return f(a, std::forward<ArgsT>(args)...);
		}
		template<class... ArgsT> auto constexpr operator()(generated_by_operation_t<InnerOperatorT, auto,auto> const& ab, ArgsT&&... args) const{
			return outer_operator(operator()(ab.first, std::forward<ArgsT>(args)...),operator()(ab.second, std::forward<ArgsT>(args)...));
		}
		template<class... ArgsT> auto constexpr operator()(generated_power_t<InnerOperatorT, SimpleScalar, auto> const& pow, ArgsT&&... args) const{
			return group::power(outer_operator, pow.exponent, operator()(pow.operand, std::forward<ArgsT>(args)...));
		}
		template<class... ArgsT> auto constexpr operator()(identity_t<InnerOperatorT>, ArgsT&&... args) const{
			return identity(OuterOperatorT{});
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
