#ifndef MULTIPLICATION_OPERATION_H
#define MULTIPLICATION_OPERATION_H 

#include"../group/operation.h"
#include"../group/commutation.h"
#include"../addition/all.h"

namespace math{
	//!Template for bilinear operations.
	template<class DerivedOperatorT>
	struct bilinear_operation_t{
		//by default, use DerivedOperatorT
		static auto constexpr apply(auto const& a, auto const& b){
			return group::operation<DerivedOperatorT>(a,b);
		}
		//operation with zero
		static auto constexpr apply(zero_t, auto const&){return zero;}
		static auto constexpr apply(auto const&, zero_t){return zero;}
		//operation with rational
		static auto constexpr apply(Ratio ratio, auto const& a){return group::power(add_operation_t{}, ratio, a);}
		static auto constexpr apply(auto const& a, Ratio ratio){return group::power(add_operation_t{}, ratio, a);}

		//factor addition power out (ka)*b=k(a*b)
		static auto constexpr apply(group::generated_power_t<add_operation_t, Ratio,auto> const& a, auto const& b){
			return group::power(add_operation_t{}, a.exponent, DerivedOperatorT::apply(a.operand,b));
		}
		//factor addition power out a*(kb)=k(a*b)
		template<class A> requires !group::Power<add_operation_t,A>
		static auto constexpr apply(A const& a, group::generated_power_t<add_operation_t, Ratio,auto> const& b){
			return group::power(add_operation_t{}, b.exponent, DerivedOperatorT::apply(a,b.operand));
		}
		
		//develop product over addition
		template<class A> requires !group::Power<add_operation_t,A>
		static auto constexpr apply(A const& a, group::generated_by_operation_t<add_operation_t, auto,auto> const& b){
			return DerivedOperatorT::apply(a,b.first)+DerivedOperatorT::apply(a,b.second);
		}
		template<class B> requires !group::Operation<add_operation_t, B> && !group::Power<add_operation_t,B>
		static auto constexpr apply(group::generated_by_operation_t<add_operation_t, auto,auto> const& a, B const& b){
			return DerivedOperatorT::apply(a.first,b)+DerivedOperatorT::apply(a.second,b);
		}
	};

	//multiplication uses bilinear rules, then operator*
	struct mult_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a*b;
		}
	};

	//one
	auto constexpr identity(mult_operation_t){return integer<1>;}
	using one_t=integer_t<1>;
	auto constexpr one=one_t{};

	//default inverse is inverse of multiplication
	template<class T> requires !group::Generated<mult_operation_t,T>
	auto constexpr inverse(mult_operation_t, T const& a){
		return inverse(a);
	}
	template<class T> requires std::is_arithmetic<T>::value
	auto constexpr inverse(T const& a){return 1./a;}

	//by default, use group operations and bilinear rules
	auto constexpr inverse(auto const& a){
		return group::inverse(mult_operation_t{}, a);
	}
	auto constexpr operator*(auto const& a, auto const& b){
		return bilinear_operation_t<mult_operation_t>::apply(a,b);
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

	//formatting
	std::ostream& operator<<(std::ostream& out, group::generated_by_operation_t<mult_operation_t, auto, auto> const& ab){
		return out<<"("<<ab.first<<") * ("<<ab.second<<")";
	}
}

#endif /* MULTIPLICATION_OPERATION_H */
