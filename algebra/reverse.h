#ifndef ALGEBRA_REVERSE_H
#define ALGEBRA_REVERSE_H 

#include"addition.h"
#include"multiplication.h"
#include"basis.h"
#include"../group/reverse.h"

namespace vector{
	constexpr auto reverse(vector::basis_element_t<auto, Scalar> const& a){
		return a;
	}
	template<class OperatorT, class A,class B> 
	constexpr auto reverse(basis_element_t<group::generated_element_t<OperatorT, A,B>, Scalar> const& ab){
		return algebra::basis_element(group::reverse(ab.element()), ab.coordinate);
	}
}

namespace algebra{
	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	constexpr auto reverse(group::generated_element_t<add_operation_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT>, auto,auto> const& ab){
		return add_operation_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT>::apply(reverse(ab.first), reverse(ab.second));
	}
}

#endif /* ALGEBRA_REVERSE_H */
