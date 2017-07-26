#ifndef ALGEBRA_H
#define ALGEBRA_H 

#include"group/concept.h"
#include"group/operation.h"
#include"sorted.h"

#include<type_traits>
#include<iostream>

namespace algebra{
	namespace hana=boost::hana;

	template<class GroupT, class IdentityT, class OperatorT, template<class> class InverseT, class ScalarT, class... ElementsT>
	concept bool BasisElementsTemplateParameters=
		   group::Group<GroupT, IdentityT, OperatorT, InverseT>
		&& std::is_arithmetic<ScalarT>::value
		&& static_cast<bool>(hana::all(hana::make_tuple(group::is_in_type_list<GroupT>(hana::type_c<ElementsT>)...)))
	;
	template<class GroupT, class IdentityT, class OperatorT, template<class> class InverseT, class ScalarT>
	concept bool ZeroBasisElementTemplateParameters=BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT>;
	template<class GroupT, class IdentityT, class OperatorT, template<class> class InverseT, class ScalarT, class ElementT>
	concept bool OneBasisElementTemplateParameters=BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>;
	template<class GroupT, class IdentityT, class OperatorT, template<class> class InverseT, class ScalarT, class ElementA, class ElementB>
	concept bool TwoBasisElementTemplateParameters=BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementA, ElementB>;

	OneBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT}
	struct basis_element_t{
		ScalarT coordinate;
	};

	OneBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT}
	auto basis_element(ElementT const& e, ScalarT const& s){
		return basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>{s};
	}
	OneBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT}
	auto basis_element(group::generated_minus_t<OperatorT, ElementT> const& a, ScalarT const& s){
		return basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>{-s};
	}

	//add operation
	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	struct add_operation_t{
		template<class ElementT> requires BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>
		using basis_element_t=algebra::basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>;

		using zero_t=group::identity_t<add_operation_t>;

		//commutation rule
		template<class ElementA, class ElementB>
			requires !std::is_same<ElementA,ElementB>::value 
			      && !Sorted<GroupT,ElementA,ElementB> 
		static constexpr auto apply(basis_element_t<ElementA> const& a, basis_element_t<ElementB> const& b){
			return apply(b,a);
		}
		//colinear rule
		template<class ElementT>
		static constexpr auto apply(basis_element_t<ElementT> const& a, basis_element_t<ElementT> const& b){
			return basis_element_t<ElementT>{a.coordinate+b.coordinate};
		}
		//group rules
		static constexpr auto apply(auto const& a, auto const& b){
			return group::operation<add_operation_t>(a,b);
		}


		static constexpr auto inverse(basis_element_t<auto> const& a){
			return std::decay_t<decltype(a)>{-a.coordinate};
		}
		static constexpr auto inverse(auto const& a){
			return group::inverse<add_operation_t>(a);
		}
	};

	//mult operation
	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	struct mult_operation_t{
		using add_operation_t=algebra::add_operation_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT>;
		template<class ElementT>
		using basis_element_t=typename add_operation_t::template basis_element_t<ElementT>;

		static constexpr auto basis_element(auto const& e, ScalarT const& s){return algebra::basis_element<GroupT, IdentityT, OperatorT, InverseT>(e,s);}

		//operation with scalar
		static constexpr auto apply(ScalarT const& a, basis_element_t<auto> const& b){
			return std::decay_t<decltype(b)>{a*b.coordinate};
		}
		static constexpr auto apply(basis_element_t<auto> const& a, ScalarT const& b){
			return apply(b,a);
		}
		template<class ElementT> requires BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>
		static constexpr auto apply(ScalarT const& a, ElementT const& b){
			return basis_element_t<ElementT>{a};
		}
		template<class ElementT> requires BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>
		static constexpr auto apply(ElementT const& a, ScalarT const& b){
			return apply(b,a);
		}
		//operation with basis vectors
		template<class ElementA, class ElementB> 
		static constexpr auto apply(basis_element_t<ElementA> const& a, basis_element_t<ElementB> const& b){
			return basis_element(OperatorT::apply(ElementA{}, ElementB{}),a.coordinate*b.coordinate);
		}
		//develop product over addition
		static constexpr auto apply(auto const& a, group::generated_element_t<add_operation_t, auto,auto> const& b){
			return add_operation_t::apply(apply(a,b.first), apply(a,b.second));
		}
		template<class B> requires !group::Generated<add_operation_t, B>
		static constexpr auto apply(group::generated_element_t<add_operation_t, auto,auto> const& a, B const& b){
			return add_operation_t::apply(apply(a.first,b), apply(a.second,b));
		}

		template<class ElementT> static constexpr auto inverse(basis_element_t<ElementT> const& a){
			return basis_element(OperatorT::inverse(ElementT{}),1/a.coordinate);
		}
	};

	//formatting
	OneBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT}
	std::ostream& operator<<(std::ostream& out, basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT> const& a){
		return out<<a.coordinate<<" * "<<ElementT{};
	}
	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	std::ostream& operator<<(std::ostream& out, group::generated_element_t<add_operation_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT>, auto, auto> const& ab){
		return out<<"("<<ab.first<<") + ("<<ab.second<<")";
	}
}

#endif /* ALGEBRA_H */
