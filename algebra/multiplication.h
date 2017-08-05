#ifndef ALGEBRA_MULTIPLICATION_H
#define ALGEBRA_MULTIPLICATION_H 

#include"basis.h"
#include"../vector/addition.h"

namespace algebra{
	template<class OperatorT, class ScalarT>
	struct mult_operation_t{
		using add_operation_t=vector::add_operation_t<ScalarT>;
		template<class ElementT>
		using basis_element_t=typename add_operation_t::template basis_element_t<ElementT>;

		//operation with scalar
		static constexpr auto apply(ScalarT const& a, basis_element_t<auto> const& b){
			return std::decay_t<decltype(b)>{a*b.coordinate};
		}
		static constexpr auto apply(basis_element_t<auto> const& a, ScalarT const& b){
			return apply(b,a);
		}
		template<class ElementT> requires !group::Generated<add_operation_t, ElementT>
		static constexpr auto apply(ScalarT const& a, ElementT const& b){
			return basis_element_t<ElementT>{a};
		}
		template<class ElementT> requires !group::Generated<add_operation_t, ElementT>
		static constexpr auto apply(ElementT const& a, ScalarT const& b){
			return apply(b,a);
		}
		//operation with zero
		static constexpr auto apply(group::identity_t<vector::add_operation_t<auto>> zero_, basis_element_t<auto> const&){
			return zero_;
		}
		static constexpr auto apply(basis_element_t<auto> const&, group::identity_t<vector::add_operation_t<auto>> zero_){
			return zero_;
		}
		//operation with basis vectors
		template<class ElementA, class ElementB> 
		static constexpr auto apply(basis_element_t<ElementA> const& a, basis_element_t<ElementB> const& b){
			return basis_element(OperatorT::apply(ElementA{}, ElementB{}),a.coordinate*b.coordinate);
		}
		//develop product over addition
		template<class ElementT> 
		static constexpr auto apply(ElementT const& a, group::generated_element_t<add_operation_t, auto,auto> const& b){
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
}

#endif /* ALGEBRA_MULTIPLICATION_H */
