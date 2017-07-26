#ifndef IDENTITY_H
#define IDENTITY_H 

#include<type_traits>

namespace group{
	template<class BinaryOperator> struct identity_t{};

	template<class ElementT, class IdentityT, class OperatorT>
	concept bool AbsorbsIdentityElement=std::is_same<decltype(OperatorT::apply(ElementT{},IdentityT{})), ElementT>::value
	                                 && std::is_same<decltype(OperatorT::apply(IdentityT{},ElementT{})), ElementT>::value
									;
} 

#endif /* IDENTITY_H */
