#ifndef ALGEBRA_H
#define ALGEBRA_H 

#include"group/concept.h"
#include"group/operation.h"
#include"sorted.h"

#include<type_traits>
#include<iostream>

namespace algebra{
	namespace hana=boost::hana;

	template<class T> concept bool Scalar=std::is_arithmetic<T>::value;

	template<class GroupT, class IdentityT, class OperatorT, template<class> class InverseT, class ScalarT, class... ElementsT>
	concept bool BasisElementsTemplateParameters=
		   group::Group<GroupT, IdentityT, OperatorT, InverseT>
		&& Scalar<ScalarT>
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

	TwoBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementA, ElementB}
	auto operator*(basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementA> const& a, basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementB> const& b){
		return basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, decltype(OperatorT::template apply(ElementA{},ElementB{}))>{a.coordinate*b.coordinate};
	}

	OneBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT}
	auto& operator<<(std::ostream& out, basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT> const& a){
		return out<<a.coordinate<<" * "<<typeid(ElementT).name();
	}


	//add rules
	TwoBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, A, B}
	constexpr auto add(A const& a, B const& b);
	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	struct add_operation_t{
		template<class A,class B>
		static auto apply(A const& a, B const& b){return add<GroupT, IdentityT, OperatorT, InverseT, ScalarT>(a,b);};

		template<class ElementT> requires BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>
		static auto inverse(basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT> const& a){
			return basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>{-a.coordinate};
		}
		template<class A>
		static auto inverse(A const& a){return group::inverse<add_operation_t>(a);}
	};
	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	using zero_t=group::identity_t<
		add_operation_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT>
	>;

	//commutations rules
	template<class GroupT, class IdentityT, class OperatorT, template<class> class InverseT, class ScalarT, class ElementA, class ElementB>
		requires !std::is_same<ElementA,ElementB>::value 
			  && TwoBasisElementTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementA, ElementB>
			  && !Sorted<GroupT,ElementA,ElementB> 
	constexpr auto add(basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementA> const& a, basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementB> const& b){
		return add<GroupT, IdentityT, OperatorT, InverseT, ScalarT>(b,a);
	}
	//colinear addition
	OneBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT}
	auto add(basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT> const& a, basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT> const& b){
		return basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>{a.coordinate+b.coordinate};
	}
	//group rules
	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	constexpr auto add(auto const& a, auto const& b){
		return group::operation<add_operation_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT>>(a,b);
	}

	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	auto& print(std::ostream& out, group::generated_element_t<add_operation_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT>, auto, auto> const& addition){
		return out<<"("<<addition.first<<") + ("<<addition.second<<")";
	}

}

#endif /* ALGEBRA_H */
