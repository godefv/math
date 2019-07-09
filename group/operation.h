#ifndef OPERATION_H
#define OPERATION_H 

#include"inverse.h"
#include"identity.h"
#include"../symbolic/symbol.h"
#include"../eval.h"

#include<type_traits>
#include<cmath>

namespace godefv::math::group{
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

	template<class OperatorT>
	auto constexpr eval_with_data(generated_by_operation_t<OperatorT,auto,auto> const& ab, auto const& eval_data){
		using godefv::math::eval_with_data;
		return OperatorT::apply(eval_with_data(ab.first, eval_data), eval_with_data(ab.second, eval_data));
	}

	//concept Operation
	template<class OperatorT, class> struct is_generated_by_operation:std::false_type{};
	template<class OperatorT, class A,class B> struct is_generated_by_operation<OperatorT, generated_by_operation_t<OperatorT,A,B>>:std::true_type{};
	template<class T, class OperatorT> concept bool Operation=is_generated_by_operation<OperatorT, T>::value;

	//concept Generated<OperatorT>
	template<class T, class OperatorT> 
	concept bool Generated=Operation<T,OperatorT> 
	                    || Power<T,OperatorT> 
	                    || std::is_same<generated_identity_t<OperatorT>,T>::value;

	//concept GeneratedByAnyOperation
	template<class T> struct is_generated_by_any_operation: std::false_type{};
	template<class T> concept bool GeneratedByAnyOperation=is_generated_by_any_operation<T>::value;

	template<class OperatorT> 
	struct is_generated_by_any_operation<group::generated_identity_t<OperatorT>>: std::true_type{};
	template<class OperatorT, class ExponentT, class OperandT> 
	struct is_generated_by_any_operation<group::generated_power_t<OperatorT,ExponentT,OperandT>>: std::true_type{};
	template<class OperatorT, class A, class B>
	struct is_generated_by_any_operation<group::generated_by_operation_t<OperatorT,A,B>>: std::true_type{};

}namespace godefv::math::geometry{
		struct compose_operation_t;
}namespace godefv::math::group{
	//default operation
	template<class OperatorT, class A, class B> 
		requires !std::is_same<A,identity_t<OperatorT>>::value 
		      && !std::is_same<B,identity_t<OperatorT>>::value 
			  && !std::is_same<OperatorT,geometry::compose_operation_t>::value
	auto constexpr operation(OperatorT, A const& a, B const& b){return generated_by_operation_t{OperatorT{},a,b};}
	//operations with identity
	template<class OperatorT> 
	auto constexpr operation(OperatorT, identity_t<OperatorT> const&, auto const& a){return a;}
	template<class OperatorT, class A> requires !std::is_same<A,identity_t<OperatorT>>::value 
	auto constexpr operation(OperatorT, A const& a, identity_t<OperatorT> const&){return a;}
	//associativity	//put everything in normalized from ((AB)C)D...
	template<class OperatorT, class A,class B,class C> 
		requires !std::is_same<A,identity_t<OperatorT>>::value
			  //&& !(std::is_base_of<generated_by_operation_t<OperatorT,B,C>, decltype(inverse(OperatorT{}, A{}))>::value && !Operation<A, OperatorT>)
	auto constexpr operation(OperatorT, A const& a, generated_by_operation_t<OperatorT,B,C> const& bc){
		return OperatorT::apply(OperatorT::apply(a, bc.first), bc.second);
	}
	//contract (ab)c=a(bc) if (bc) can be processed
	template<class OperatorT, class A,class B,class C> 
		requires !Operation<B,OperatorT> 
		      && !Operation<C,OperatorT> 
			  && !std::is_base_of<generated_by_operation_t<OperatorT,B,C>, decltype(OperatorT::apply(B{},C{}))>::value 
			  && !std::is_same<C,identity_t<OperatorT>>::value
	auto constexpr operation(OperatorT, generated_by_operation_t<OperatorT,A,B> const& ab, C const& c){
		return OperatorT::apply(ab.first, OperatorT::apply(ab.second,c));
	}

	//(a power x) op a = a op (a power x) = a power (a+1)
	template<class OperatorT, Symbol SymbolT, SimpleScalar ExponentT> auto constexpr operation(OperatorT, generated_power_t<OperatorT, ExponentT, SymbolT> const& a, SymbolT){return power(OperatorT{}, a.exponent+integer<1>, SymbolT{});}
	template<class OperatorT, Symbol SymbolT, SimpleScalar ExponentT> auto constexpr operation(OperatorT, SymbolT, generated_power_t<OperatorT, ExponentT, SymbolT> const& b){return power(OperatorT{}, b.exponent+integer<1>, SymbolT{});}

	//(a power x) op (a power y) = a power (x+y)
	template<class OperatorT, SimpleScalar Exponent1, SimpleScalar Exponent2, Symbol SymbolT>
	auto constexpr operation(OperatorT, generated_power_t<OperatorT, Exponent1, SymbolT> const& ax, generated_power_t<OperatorT, Exponent2, SymbolT> const& ay){
		return power(OperatorT{}, ax.exponent+ay.exponent, SymbolT{});
	}

	//a op a = a power 2
	template<class OperatorT, Symbol SymbolT> requires !Generated<SymbolT,OperatorT>
	auto constexpr operation(OperatorT, SymbolT,SymbolT){
		return power(OperatorT{}, integer<2>, SymbolT{});
	}

	//inverse of product
	template<class OperatorT, class A,class B> 
	auto constexpr inverse(OperatorT op, generated_by_operation_t<OperatorT, A,B> const& ab){
		return OperatorT::apply(inverse(op, ab.second), inverse(op, ab.first));
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

namespace godefv::math{
	template<class OperatorT, Symbol A, Symbol B> struct is_symbol<group::generated_by_operation_t<OperatorT,A,B>>: std::true_type{};
	template<class OperatorT, Scalar A, Scalar B> struct is_scalar<group::generated_by_operation_t<OperatorT,A,B>>: std::true_type{};
}

#endif /* OPERATION_H */
