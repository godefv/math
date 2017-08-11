#ifndef ALGEBRA_BASIS_H
#define ALGEBRA_BASIS_H 

#include"../vector/basis.h"
#include"../vector/addition.h"
#include"../group/minus.h"

#include<boost/hana.hpp>

namespace algebra{
	template<class ElementT, vector::Scalar ScalarT> 
	constexpr auto basis_element(ElementT const&, ScalarT const& s){
		return vector::basis_element_t<ElementT, ScalarT>{s};
	}
	template<class OperatorT, class ElementT, vector::Scalar ScalarT> 
	constexpr auto basis_element(group::generated_minus_t<OperatorT, ElementT> const&, ScalarT const& s){
		return vector::basis_element_t<ElementT, ScalarT>{-s};
	}
	constexpr auto basis_element(group::identity_t<vector::add_operation_t<auto>> a, vector::Scalar const&){
		return a;
	}
}

#endif /* ALGEBRA_BASIS_H */
