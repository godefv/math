#ifndef ALGEBRA_MULTIPLICATION_H
#define ALGEBRA_MULTIPLICATION_H 

#include"basis.h"
#include"../vector/addition.h"

namespace algebra{
	template<class OperatorT>
	struct mult_operation_t{
		//operation with scalar
		static constexpr auto apply(vector::Scalar const& a, vector::basis_element_t<auto> const& b){
			return std::decay_t<decltype(b)>{b.element, a*b.coordinate};
		}
		static constexpr auto apply(vector::basis_element_t<auto> const& a, vector::Scalar const& b){
			return apply(b,a);
		}
		template<class ElementT> requires !group::Generated<vector::add_operation_t, ElementT>
		static constexpr auto apply(vector::Scalar const& a, ElementT const& e){
			return vector::basis_element_t{e,a};
		}
		template<class ElementT> requires !group::Generated<vector::add_operation_t, ElementT>
		static constexpr auto apply(ElementT const& a, vector::Scalar const& b){
			return apply(b,a);
		}
		//operation with zero
		static constexpr auto apply(group::identity_t<vector::add_operation_t> zero_, vector::basis_element_t<auto> const&){
			return zero_;
		}
		static constexpr auto apply(vector::basis_element_t<auto> const&, group::identity_t<vector::add_operation_t> zero_){
			return zero_;
		}
		//operation with basis vectors
		static constexpr auto apply(vector::basis_element_t<auto> const& a, vector::basis_element_t<auto> const& b){
			return basis_element(OperatorT::apply(a.element, b.element),a.coordinate*b.coordinate);
		}
		//develop product over addition
		static constexpr auto apply(auto const& a, group::generated_element_t<vector::add_operation_t, auto,auto> const& b){
			return vector::add_operation_t::apply(apply(a,b.first), apply(a,b.second));
		}
		template<class B> requires !group::Generated<vector::add_operation_t, B>
		static constexpr auto apply(group::generated_element_t<vector::add_operation_t, auto,auto> const& a, B const& b){
			return vector::add_operation_t::apply(apply(a.first,b), apply(a.second,b));
		}

		static constexpr auto inverse(vector::Scalar const& a){return 1/a;}
		static constexpr auto inverse(vector::basis_element_t<auto> const& a){
			return basis_element(OperatorT::inverse(a.element),inverse(a.coordinate));
		}
	};
}

#endif /* ALGEBRA_MULTIPLICATION_H */
