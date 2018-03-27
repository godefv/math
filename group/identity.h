#ifndef IDENTITY_H
#define IDENTITY_H 

#include<type_traits>
#include<iostream>

namespace math::group{
	template<class Operator> struct identity_t{
		Operator operation;
	};

	//overloadable constructor
	template<class OperatorT> auto constexpr identity(OperatorT){return identity_t<OperatorT>{};}

	template<class ElementT, class IdentityT, class OperatorT>
	concept bool AbsorbsIdentityElement=std::is_same<decltype(OperatorT::apply(ElementT{},IdentityT{})), ElementT>::value
	                                 && std::is_same<decltype(OperatorT::apply(IdentityT{},ElementT{})), ElementT>::value
									;

	template<class Operator>
	bool constexpr operator==(identity_t<Operator> const&, identity_t<Operator> const&){
		return true;
	}
	template<class Operator>
	bool constexpr operator!=(identity_t<Operator> const& a, identity_t<Operator> const& b){
		return !(a==b);
	}

	template<class BinaryOperator>
	std::ostream& operator<<(std::ostream& out, identity_t<BinaryOperator> const&){
		return out<<"id<"<<typeid(BinaryOperator).name()<<">";
	}
} 

#endif /* IDENTITY_H */
