#ifndef OPERATION_H
#define OPERATION_H 

#include"inverse.h"
#include"identity.h"
#include"minus.h"

#include<type_traits>
#include<cmath>

namespace math::group{
	//generated_by_operation_t
	template<class OperatorT, class A,class B> struct generated_by_operation_t{
		OperatorT operation;
		A first; B second;
	};
	template<class OperatorT, class A,class B> generated_by_operation_t(OperatorT,A,B)->generated_by_operation_t<OperatorT,A,B>;

	template<class OperatorT, class A,class B>
	bool operator==(generated_by_operation_t<OperatorT, A,B> const& a, generated_by_operation_t<OperatorT, A,B> const& b){
		return a.first==b.first && a.second==b.second;
	}
	bool operator==(generated_by_operation_t<auto, auto,auto> const& a, generated_by_operation_t<auto, auto,auto> const& b){
		return false;
	}
	bool operator!=(generated_by_operation_t<auto, auto,auto> const& a, generated_by_operation_t<auto, auto,auto> const& b){
		return !(a==b);
	}

	std::ostream& operator<<(std::ostream& out, group::generated_by_operation_t<auto, auto, auto> const& ab){
		return out<<typeid(ab.operation).name()<<"("<<ab.first<<", "<<ab.second<<")";
	}

	//concepts
	template<class OperatorT, class> struct is_generated_by_operation:std::false_type{};
	template<class OperatorT, class A,class B> struct is_generated_by_operation<OperatorT, generated_by_operation_t<OperatorT,A,B>>:std::true_type{};
	template<class OperatorT, class T> concept bool Operation=is_generated_by_operation<OperatorT, T>::value;

	template<class OperatorT, class T> 
	concept bool Generated=Operation<OperatorT,T> 
	                    || Minus<OperatorT,T> 
	                    || Power<OperatorT,T> 
	                    || std::is_same<identity_t<OperatorT>,T>::value;

	//default operation
	template<class OperatorT, class A,class B> 
	auto constexpr operation(A const& a, B const& b){return generated_by_operation_t{OperatorT{},a,b};}
	//operations with identity
	template<class OperatorT, class A> 
	auto constexpr operation(identity_t<OperatorT> const&, A const& a){return a;}
	template<class OperatorT, class A> requires !std::is_same<A,identity_t<OperatorT>>::value 
	auto constexpr operation(A const& a, identity_t<OperatorT> const&){return a;}
	//operations with minus
	template<class OperatorT, class A,class B> 
		requires !std::is_same<A, identity_t<OperatorT>>::value
		      && !(std::is_same<generated_minus_t<OperatorT, B>, inverse_t<OperatorT, A>>::value && !Operation<OperatorT, A>)
	auto constexpr operation(A const&, generated_minus_t<OperatorT, B> const&){
		return group::minus_t<OperatorT, decltype(OperatorT::apply(A{},B{}))>{};
	}
	template<class OperatorT, class A,class B> 
		requires !std::is_same<A, identity_t<OperatorT>>::value
		      && !std::is_same<A, inverse_t<OperatorT, generated_minus_t<OperatorT, B>>>::value
			  && !Minus<OperatorT,A>
	auto constexpr operation(generated_minus_t<OperatorT, B> const&, A const&){
		return group::minus_t<OperatorT, decltype(OperatorT::apply(B{},A{}))>{};
	}
	//associativity	//put everything in normalized from ((AB)C)D...
	template<class OperatorT, class A,class B,class C> 
		requires !std::is_same<A,identity_t<OperatorT>>::value
		      && !(std::is_same<generated_by_operation_t<OperatorT,B,C>, inverse_t<OperatorT, A>>::value && !Operation<OperatorT, A>)
			  && !Minus<OperatorT,A>
	auto constexpr operation(A const& a, generated_by_operation_t<OperatorT,B,C> const& bc){
		return OperatorT::apply(OperatorT::apply(a, bc.first), bc.second);
	}
	//collapse operations as much as possible
	template<class OperatorT, class A,class B,class C> 
		requires !Operation<OperatorT,B> 
		      && !Operation<OperatorT,C> 
			  && !Minus    <OperatorT,C>
			  && !std::is_same<decltype(OperatorT::apply(B{},C{})), generated_by_operation_t<OperatorT,B,C>>::value 
			  && !std::is_same<C,identity_t<OperatorT>>::value
	auto constexpr operation(generated_by_operation_t<OperatorT,A,B> const& ab, C const& c){
		return OperatorT::apply(ab.first, OperatorT::apply(ab.second,c));
	}
	//(a power x) times (b power x) equals (a times b) power x <= not true if a and b does not commute !
	//template<Ratio RatioT, class A, class B> requires !std::is_same<A,B>::value
	//auto constexpr operation(generated_power_t<OperatorT, RatioT, A> const& a, generated_power_t<OperatorT, RatioT, B> const& b){
		//return power(OperatorT{}, RatioT{}, a.operand*b.operand);
	//}

	//(a power x) times a = a times (a power x) = a power (a+1)
	template<class OperatorT, Symbol SymbolT, Ratio RatioT> auto constexpr operation(generated_power_t<OperatorT, RatioT, SymbolT>, SymbolT){return power(OperatorT{}, RatioT{}+integer<1>, SymbolT{});}
	template<class OperatorT, Symbol SymbolT, Ratio RatioT> auto constexpr operation(SymbolT, generated_power_t<OperatorT, RatioT, SymbolT>){return power(OperatorT{}, RatioT{}+integer<1>, SymbolT{});}

	//(a power x) times (a power y) = a power (x+y)
	template<class OperatorT, Ratio Ratio1, Ratio Ratio2, Symbol SymbolT>
	auto constexpr operation(generated_power_t<OperatorT, Ratio1, SymbolT>, generated_power_t<OperatorT, Ratio2, SymbolT>){
		return power(OperatorT{}, Ratio1{}+Ratio2{}, SymbolT{});
	}

	//a times a = a power 2
	template<class OperatorT, Symbol SymbolT> requires !Power<OperatorT,SymbolT>
	auto constexpr operation(SymbolT,SymbolT){
		return power(OperatorT{}, integer<2>, SymbolT{});
	}

	//inverse of product
	template<class OperatorT, class A,class B> 
	auto constexpr inverse(OperatorT op, generated_by_operation_t<OperatorT, A,B> const& ab){
		return OperatorT::apply(inverse(op, ab.second), inverse(op, ab.first));
	}
	//inverse of minus A
	template<class OperatorT, class A> 
	auto constexpr inverse(OperatorT op, generated_minus_t<OperatorT, A> const& a){
		return minus_t<OperatorT, decltype(inverse(op, a.value))>{};
	}

	//number of terms in operation
	template<class OperatorT> 
	int constexpr number_of_terms(auto const& a){
		return 1;
	}
	template<class OperatorT> 
	int constexpr number_of_terms(generated_by_operation_t<OperatorT,auto,auto> const& ab){
		return number_of_terms<OperatorT>(ab.first)+number_of_terms<OperatorT>(ab.second);
	}

}

#endif /* OPERATION_H */
