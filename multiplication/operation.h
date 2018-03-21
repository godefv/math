#ifndef MULTIPLICATION_OPERATION_H
#define MULTIPLICATION_OPERATION_H 

#include"../group/operation.h"
#include"../group/commutation.h"
#include"../addition/operation.h"

namespace math{
	struct mult_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a*b;
		}
	};
	using one_t=group::identity_t<mult_operation_t>;
	auto constexpr one=one_t{};

	template<class T> requires !group::Generated<mult_operation_t,T>
	auto constexpr inverse(mult_operation_t, T const& a){
		return inverse(a);
	}

	//by default, use group operations
	auto constexpr inverse(auto const& a){
		return group::inverse(mult_operation_t{}, a);
	}
	auto constexpr inverse(SimpleScalar const& a){return 1./a;}
	auto constexpr operator*(auto const& a, auto const& b){
		return group::operation<mult_operation_t>(a,b);
	}
	auto constexpr operator/(auto const& a, auto const& b){
		return a*inverse(b);
	}

   	//commutation rule
   	template<class A, class B>
   		requires !std::is_same<A,B>::value 
		      && !group::Operation<mult_operation_t,A>
		      && !group::Operation<mult_operation_t,B>
   		      && static_compare(mult_operation_t{}, A{},B{})<0
		      && (Scalar<A>||Scalar<B>) // scalars commute with everything
   	auto constexpr operator*(A const& a, B const& b){
   		return b*a;
   	}
	//operation with zero
	auto constexpr operator*(zero_t, auto const&){return zero;}
	auto constexpr operator*(auto const&, zero_t){return zero;}
	//operation with rational
	auto constexpr operator*(Ratio ratio, auto const& a){return group::power(add_operation_t{}, ratio, a);}
	//develop product over addition
	auto constexpr operator*(auto const& a, group::generated_by_operation_t<add_operation_t, auto,auto> const& b){
		return a*b.first+a*b.second;
	}
	template<class B> requires !group::Operation<add_operation_t, B>
	auto constexpr operator*(group::generated_by_operation_t<add_operation_t, auto,auto> const& a, B const& b){
		return a.first*b+a.second*b;
	}

	//formatting
	std::ostream& operator<<(std::ostream& out, group::generated_by_operation_t<mult_operation_t, auto, auto> const& ab){
		return out<<"("<<ab.first<<") * ("<<ab.second<<")";
	}

	//addition nth power of x equals n*x
	auto constexpr generated_power(add_operation_t, Ratio exponent, auto const& operand){
		return exponent*operand;
	}
}

#endif /* MULTIPLICATION_OPERATION_H */
