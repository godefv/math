#ifndef BASIS_H
#define BASIS_H 

#include"scalar.h"

namespace vector{
	template<class ElementT, Scalar ScalarT=double> 
	struct basis_element_t{
		ScalarT coordinate;

		auto constexpr element() const{return ElementT{};}
	};

	constexpr int static_compare(basis_element_t<auto,auto> const& a, basis_element_t<auto,auto> const& b){return static_compare(a.element(),b.element());}

	template<class ElementT> 
	bool constexpr operator==(basis_element_t<ElementT, Scalar> const& a, basis_element_t<ElementT, Scalar> const& b){
		return a.coordinate==b.coordinate;
	}
	bool constexpr operator==(basis_element_t<auto, Scalar> const& a, basis_element_t<auto, Scalar> const& b){
		return false;
	}
	bool constexpr operator!=(basis_element_t<auto, Scalar> const& a, basis_element_t<auto, Scalar> const& b){
		return !(a==b);
	}

	template<class ElementT, Scalar ScalarT> 
	auto constexpr operator*(Scalar const& a, basis_element_t<ElementT, ScalarT> const& b){
		return basis_element_t<ElementT, ScalarT>{a*b.coordinate};
	}
	template<class ElementT> 
	auto constexpr operator*(basis_element_t<ElementT, Scalar> const& a, Scalar const& b){
		return b*a;
	}
}

#endif /* BASIS_H */
