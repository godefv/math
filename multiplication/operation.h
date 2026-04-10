#ifndef MULTIPLICATION_OPERATION_H
#define MULTIPLICATION_OPERATION_H 

#include"../group/operation.h"
#include"../group/commutation.h"
#include"../addition/all.h"

#include<type_traits>

namespace godefv::math{
	//!Template for bilinear operations.
	template<class DerivedOperatorT>
	struct bilinear_operation_t{
		template<class A, class B>
		static auto constexpr apply(A const& a, B const& b){
			//operation with zero
			if constexpr(Zero<A> || Zero<B>){
				return zero;
			//operation with scalar (left)
			}else if constexpr(Scalar<A>
			      && (!Symbol<A> || SimpleScalar<A>)
			      && !group::Generated<A,DerivedOperatorT>
			){
				return group::power(add_operation_t{}, a, b);
			//operation with scalar (right)
			}else if constexpr(Scalar<B>
			      && (!Symbol<B> || SimpleScalar<B>)
			      && !group::Generated<B,DerivedOperatorT>
			){
				return group::power(add_operation_t{}, b, a);
			}else{
				return group::operation(DerivedOperatorT{},a,b);
			}
		}

		//factor addition power out (ka)*b=k(a*b)
		template<Scalar ExponentT, class X>
		static auto constexpr apply(group::generated_power_t<add_operation_t, ExponentT,X> const& a, auto const& b){
			return group::power(add_operation_t{}, a.exponent, DerivedOperatorT::apply(a.operand,b));
		}
		//factor addition power out a*(kb)=k(a*b)
		template<class A, Scalar ExponentT, class X> requires (!group::Power<A,add_operation_t>)
		static auto constexpr apply(A const& a, group::generated_power_t<add_operation_t, ExponentT,X> const& b){
			return group::power(add_operation_t{}, b.exponent, DerivedOperatorT::apply(a,b.operand));
		}
		
		//develop product over addition a(b+c)=ab+ac
		template<class A, class B, class C> requires (!group::Power<A,add_operation_t>)
		static auto constexpr apply(A const& a, group::generated_by_operation_t<add_operation_t, B,C> const& bc){
			return DerivedOperatorT::apply(a,bc.first)+DerivedOperatorT::apply(a,bc.second);
		}
		//develop product over addition (a+b)c=ac+bc
		template<class A, class B, class C> requires (!group::Operation<C,add_operation_t> && !group::Power<C,add_operation_t>)
		static auto constexpr apply(group::generated_by_operation_t<add_operation_t, A,B> const& ab, C const& c){
			return DerivedOperatorT::apply(ab.first,c)+DerivedOperatorT::apply(ab.second,c);
		}

	};

	//multiplication uses bilinear rules, then operator*
	struct mult_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a*b;
		}
		auto constexpr operator()(auto const& a, auto const& b) const{
			return std::decay_t<decltype(*this)>::apply(a,b);
		}
	};

	//one
	auto constexpr identity(mult_operation_t){return integer<1>;}
	using one_t=integer_t<1>;
	auto constexpr one=one_t{};

	auto constexpr inverse(Number auto const& a){return 1./a;}
	//default inverse is inverse of multiplication
	template<class T> requires (!group::Generated<T,mult_operation_t>)
	auto constexpr inverse(mult_operation_t, T const& a){
		return inverse(a);
	}

	//by default, use group operations and bilinear rules
	auto constexpr inverse(NonSimpleScalarExpression auto const& a){
		return group::inverse(mult_operation_t{}, a);
	}
	template<Expression A, Expression B> 
		requires ((NonSimpleScalar<A> || NonSimpleScalar<B>)
		&& (
		   ((NonScalar<A> && NonScalar<B>) || !(static_compare(mult_operation_t{}, A{},B{})<0))
		|| group::Operation<A,mult_operation_t>
		|| group::Operation<B,mult_operation_t>
		))
	auto constexpr operator*(A const& a, B const& b){
		return bilinear_operation_t<mult_operation_t>::apply(a,b);
	}
   	template<Expression A, class B> requires ((NonSimpleScalar<A> || NonSimpleScalar<B>) && requires(B b){inverse(b);})
	auto constexpr operator/(A const& a, B const& b){
		return a*inverse(b);
	}

   	//commutation rule
   	template<Expression A, Expression B>
   	requires((!SimpleScalar<A> || !SimpleScalar<B>) //avoid negating a boolean expression inside constraints, see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=67070
   	      && !std::is_same_v<A,B> 
	      && !group::Operation<A,mult_operation_t>
	      && !group::Operation<B,mult_operation_t>
   	      && static_compare(mult_operation_t{}, A{},B{})<0
	      && (Scalar<A>||Scalar<B>) // scalars commute with everything
	)
   	auto constexpr operator*(A const& a, B const& b){
   		return b*a;
   	}

	//contract ab+ac=a(b+c) if (b+c) can be processed
	template<Symbol A, class B, class C> 
	requires(!std::is_same_v<decltype(B{}+C{}), group::generated_by_operation_t<add_operation_t,B,C>> 
	      && !(Symbol<B> && std::is_same_v<B,C>) //else we have ab+ab=2ab
	)
	static auto constexpr operator+(group::generated_by_operation_t<mult_operation_t, A,B> const& ab, group::generated_by_operation_t<mult_operation_t, A,C> const& ac){
		using ::operator+;
		return A{}*(ab.second+ac.second);
	}
	//contract ac+bc=(a+b)c if (a+b) can be processed
	template<class A, class B, Symbol C> 
	requires(!std::is_same_v<decltype(A{}+B{}), group::generated_by_operation_t<add_operation_t,A,B>> 
	      && !(Symbol<B> && std::is_same_v<A,B>) //else we have ac+ac=2ac
	)
	static auto constexpr operator+(group::generated_by_operation_t<mult_operation_t, A,C> const& ac, group::generated_by_operation_t<mult_operation_t, B,C> const& bc){
		using ::operator+;
		return (ac.first+bc.first)*C{};
	}
	//contract ab+kac=a(b+kc) if (b+kc) can be processed
	template<Symbol A, class B, class C, class K> 
	requires(!std::is_same_v<decltype(B{}+K{}*C{}), group::generated_by_operation_t<add_operation_t,B,group::generated_power_t<add_operation_t,K,C>>> 
	      && !(Symbol<B> && std::is_same_v<B,C>) //else we have ab+kab=(1+k)ab
	)
	static auto constexpr operator+(group::generated_by_operation_t<mult_operation_t, A,B> const& ab, group::generated_power_t<add_operation_t, K, group::generated_by_operation_t<mult_operation_t, A,C>> const& kac){
		using ::operator+;
		return A{}*(ab.second+kac.exponent*kac.operand.second);
	}
	//contract ac+kbc=(a+kb)c if (a+kb) can be processed
	template<class A, class B, Symbol C, class K> 
	requires(!std::is_same_v<decltype(A{}+K{}*B{}), group::generated_by_operation_t<add_operation_t,A,group::generated_power_t<add_operation_t,K,B>>> 
	      && !(Symbol<B> && std::is_same_v<A,B>) //else we have ac+kac=(1+k)ac
	)
	static auto constexpr operator+(group::generated_by_operation_t<mult_operation_t, A,C> const& ac, group::generated_power_t<add_operation_t, K, group::generated_by_operation_t<mult_operation_t, B,C>> const& kbc){
		using ::operator+;
		return (ac.first+kbc.exponent*kbc.operand.first)*C{};
	}
	//contract kab+ac=a(kb+c) if (kb+c) can be processed
	//contract kac+bc=(ka+b)c if (ka+b) can be processed
	//done because we collapse ka+b as k(a+b/k) if a+b/k can be processed

	//ab>=0 if a,b>=0
	template<PositiveScalar A, PositiveScalar B>
	auto constexpr operator>=(group::generated_by_operation_t<mult_operation_t,A,B>, zero_t){return std::true_type{};}
	
	//formatting
	namespace detail{
		std::ostream& format_multiplication_operand(std::ostream& out, auto const& operand){
			return out<<"("<<operand<<")";
		}
		std::ostream& format_multiplication_operand(std::ostream& out, group::Generated<mult_operation_t> auto const& operand){
			return out<<operand;
		}
	}
	template<class A, class B>
	std::ostream& operator<<(std::ostream& out, group::generated_by_operation_t<mult_operation_t, A, B> const& ab){
		detail::format_multiplication_operand(out, ab.first);
		out<<" * ";
		detail::format_multiplication_operand(out, ab.second);
		return out;
	}
}

#endif /* MULTIPLICATION_OPERATION_H */
