#ifndef ALGEBRA_BASIS_H
#define ALGEBRA_BASIS_H 

#include"../vector/basis.h"
#include"../group/concept.h"
#include"../group/minus.h"

#include<boost/hana.hpp>

namespace algebra{
	template<class ElementT, vector::Scalar ScalarT> 
	constexpr auto basis_element(ElementT const& e, ScalarT const& s){
		return vector::basis_element_t<ElementT, ScalarT>{s};
	}
	template<class OperatorT, class ElementT, vector::Scalar ScalarT> 
	constexpr auto basis_element(group::generated_minus_t<OperatorT, ElementT> const& a, ScalarT const& s){
		return vector::basis_element_t<ElementT, ScalarT>{-s};
	}
}

#endif /* ALGEBRA_BASIS_H */
