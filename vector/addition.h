#ifndef ADDITION_H
#define ADDITION_H 

#include"basis.h"
#include"../group/commutation.h"
#include"../group/operation.h"
#include"../group/inverse.h"
#include"../group/minus.h"

#include<iostream>

namespace vector{
	//addition definition
	struct add_operation_t{
		//commutation rule
		template<class ElementA, class ElementB>
			requires !std::is_same<ElementA,ElementB>::value 
			      && static_compare(ElementA{},ElementB{})<0
		static constexpr auto apply(basis_element_t<ElementA,auto> const& a, basis_element_t<ElementB,auto> const& b){
			return apply(b,a);
		}
		//colinear rule
		template<class ElementT>
		static constexpr auto apply(basis_element_t<ElementT,auto> const& a, basis_element_t<ElementT,auto> const& b);
		//group rules
		static constexpr auto apply(auto const& a, auto const& b){
			return group::operation<add_operation_t>(a,b);
		}

		static constexpr auto inverse(basis_element_t<auto,auto> const& a);
		static constexpr auto inverse(auto const& a){
			return group::inverse<add_operation_t>(a);
		}
	};
	using zero_t=group::identity_t<add_operation_t>;
	auto constexpr zero=zero_t{};


	//basis_element_t constructors
	constexpr auto basis_element(auto const&, vector::Zero){
		return zero;
	}
	constexpr auto basis_element(auto const& element, vector::NonZeroScalar const& s){
		return vector::basis_element_t{element,s};
	}
	constexpr auto basis_element(group::generated_minus_t<auto, auto> const& a, vector::NonZeroScalar const& s){
		return vector::basis_element_t{a.value,-s};
	}
	constexpr auto basis_element(group::identity_t<vector::add_operation_t>, vector::NonZeroScalar const&){
		return zero;
	}

	//addition specialisations which depend on basis_element
	template<class ElementT>
	constexpr auto add_operation_t::apply(basis_element_t<ElementT,auto> const& a, basis_element_t<ElementT,auto> const& b){
		return vector::basis_element(a.element, a.coordinate+b.coordinate);
	}
	//group rules
	constexpr auto add_operation_t::inverse(basis_element_t<auto,auto> const& a){
		return vector::basis_element(a.element, -a.coordinate);
	}

	std::ostream& operator<<(std::ostream& out, group::generated_element_t<add_operation_t, auto, auto> const& ab){
		return out<<"("<<ab.first<<") + ("<<ab.second<<")";
	}

}

#endif /* ADDITION_H */
