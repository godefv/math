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
		//scalar rule
		Scalar{Scalar2}
		static constexpr auto apply(Scalar a, Scalar2 b){
			return a+b;
		}
		//group rules
		static constexpr auto apply(auto const& a, auto const& b){
			return group::operation<add_operation_t>(a,b);
		}

		static constexpr auto inverse(basis_element_t<auto,auto> const& a);
		static constexpr auto inverse(Scalar a){return -a;}
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
	constexpr auto basis_element(auto const& element, vector::NonZero const& s){
		return vector::basis_element_t{element,s};
	}
	constexpr auto basis_element(group::generated_minus_t<auto, auto> const& a, vector::NonZero const& s){
		return vector::basis_element_t{a.value,-s};
	}
	constexpr auto basis_element(group::identity_t<vector::add_operation_t>, vector::NonZero const&){
		return zero;
	}

	//addition specialisations which depend on basis_element
	template<class ElementT>
	constexpr auto add_operation_t::apply(basis_element_t<ElementT,auto> const& a, basis_element_t<ElementT,auto> const& b){
		return vector::basis_element(a.element, add_operation_t::apply(a.coordinate, b.coordinate));
	}
	//group rules
	constexpr auto add_operation_t::inverse(basis_element_t<auto,auto> const& a){
		return vector::basis_element(a.element, add_operation_t::inverse(a.coordinate));
	}

	//concepts
	template<class T> bool concept Vector=BasisVector<T> || group::Generated<T,add_operation_t> || std::is_same<T,group::identity_t<add_operation_t>>::value;

	//operators
	auto constexpr operator-(Vector const& a){
		return vector::add_operation_t::inverse(a);
	}
	Vector{Vector2}
	auto constexpr operator+(Vector const& a, Vector2 const& b){
		return vector::add_operation_t::apply(a,b);
	}
	Vector{Vector2}
	auto constexpr operator-(Vector const& a, Vector2 const& b){
		return a+(-b);
	}

	std::ostream& operator<<(std::ostream& out, group::generated_element_t<add_operation_t, auto, auto> const& ab){
		return out<<"("<<ab.first<<") + ("<<ab.second<<")";
	}

}

#endif /* ADDITION_H */
