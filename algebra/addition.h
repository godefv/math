#ifndef ALGEBRA_ADDITION_H
#define ALGEBRA_ADDITION_H 

#include"basis.h"
#include"../vector/addition.h"
#include"../group/operation.h"
#include"../group/inverse.h"
#include"../sorted.h"

#include<type_traits>

namespace algebra{
	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	struct add_operation_t: vector::add_operation_t<ScalarT>{
		template<class ElementT>
		using basis_element_t=typename vector::add_operation_t<ScalarT>::template basis_element_t<ElementT>;

		using vector::add_operation_t<ScalarT>::apply;
		using vector::add_operation_t<ScalarT>::inverse;

		//commutation rule
		template<class ElementA, class ElementB>
			requires !std::is_same<ElementA,ElementB>::value 
			      && !Sorted<GroupT,ElementA,ElementB> 
		static constexpr auto apply(basis_element_t<ElementA> const& a, basis_element_t<ElementB> const& b){
			return apply(b,a);
		}
		//group rules
		static constexpr auto apply(auto const& a, auto const& b){
			return group::operation<add_operation_t>(a,b);
		}

		static constexpr auto inverse(auto const& a){
			return group::inverse<add_operation_t>(a);
		}
	};
}

#endif /* ALGEBRA_ADDITION_H */
