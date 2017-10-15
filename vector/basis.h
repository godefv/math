#ifndef BASIS_H
#define BASIS_H 

#include"scalar.h"
#include"../symbolic/eval.h"

#include<iostream>
#include<cmath>

namespace vector{
	template<class ElementT, class ScalarT=double> 
	struct basis_element_t{
		ElementT element;
		ScalarT coordinate;
	};
	template<class ElementT, class ScalarT> basis_element_t(ElementT,ScalarT)->basis_element_t<ElementT,ScalarT>;

	int constexpr static_compare(basis_element_t<auto,auto> const& a, basis_element_t<auto,auto> const& b){
		return static_compare(a.element,b.element);
	}

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

	//eval
	using ::eval;
	template<class, class=void> 
	struct is_eval_to_scalar: std::false_type{};
	template<class ElementT, class ScalarT> 
	struct is_eval_to_scalar<basis_element_t<ElementT,ScalarT>, std::void_t<decltype(eval(std::declval<ElementT&>())*eval(std::declval<ScalarT&>()))>>: std::true_type{};

	auto constexpr eval(basis_element_t<auto,auto> const& a){
		if constexpr(is_eval_to_scalar<std::decay_t<decltype(a)>>::value){
			return eval(a.element)*eval(a.coordinate);
		}else{
			return basis_element_t{eval(a.element),eval(a.coordinate)};
		}
	}

	//operations
	auto constexpr abs(basis_element_t<auto,auto> const& a){
		using std::abs;
		return basis_element_t{abs(a.element),abs(a.coordinate)};
	}
	auto constexpr sqrt(basis_element_t<auto,auto> const& a){
		using std::sqrt;
		return basis_element_t{sqrt(a.element),sqrt(a.coordinate)};
	}

	//concepts
	template<class T> struct is_basis_vector:std::false_type{};
	template<class ElementT, Scalar ScalarT> struct is_basis_vector<basis_element_t<ElementT,ScalarT>>:std::true_type{};
	template<class T> concept bool BasisVector=is_basis_vector<T>::value;
}

#endif /* BASIS_H */
