#ifndef BASIS_H
#define BASIS_H 

#include"scalar.h"

#include<iostream>

namespace vector{
	template<class ElementT, Scalar ScalarT=double> 
	struct basis_element_t{
		ElementT element;
		ScalarT coordinate;
	};
	template<class ElementT, Scalar ScalarT> basis_element_t(ElementT,ScalarT)->basis_element_t<ElementT,ScalarT>;

	constexpr int static_compare(basis_element_t<auto,auto> const& a, basis_element_t<auto,auto> const& b){return static_compare(a.element,b.element);}

	template<class ElementT> 
	bool constexpr operator==(basis_element_t<ElementT, auto> const& a, basis_element_t<ElementT, auto> const& b){
		return a.coordinate==b.coordinate;
	}
	bool constexpr operator==(basis_element_t<auto, auto> const& a, basis_element_t<auto, auto> const& b){
		return false;
	}
	bool constexpr operator!=(basis_element_t<auto, auto> const& a, basis_element_t<auto, auto> const& b){
		return !(a==b);
	}

	auto constexpr operator*(Scalar const& a, basis_element_t<auto, auto> const& b){
		return basis_element_t{b.element,a*b.coordinate};
	}
	auto constexpr operator*(basis_element_t<auto, auto> const& a, Scalar const& b){
		return b*a;
	}

	std::ostream& operator<<(std::ostream& out, basis_element_t<auto, auto> const& a){
		return out<<a.coordinate<<" * "<<a.element;
	}
}

#endif /* BASIS_H */
