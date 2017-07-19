#ifndef IDENTITY_H
#define IDENTITY_H 

#include"apply_operation.h"

#include<type_traits>

namespace group{
	template<class BinaryOperator> struct identity_t{};

	template<class ElementT, class IdentityT, class OperatorT>
	concept bool AbsorbsIdentityElement=std::is_same<decltype(apply_operation<OperatorT>(ElementT{},IdentityT{})), ElementT>::value
	                                 && std::is_same<decltype(apply_operation<OperatorT>(IdentityT{},ElementT{})), ElementT>::value
									;
} 

#endif /* IDENTITY_H */
