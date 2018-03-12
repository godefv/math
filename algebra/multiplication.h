#ifndef ALGEBRA_MULTIPLICATION_H
#define ALGEBRA_MULTIPLICATION_H 

#include"../symbolic/rational.h"
#include"../symbolic/operation/template.h"
#include"../vector/basis.h"
#include"../vector/addition.h"

namespace vector{
	constexpr auto basis_vector(basis_vector_t<auto,auto> const& element, vector::NonZero const& scalar){
		return element*scalar;
	}
	constexpr auto basis_vector(symbolic::Ratio const& element, vector::NonZero const& scalar){
		return element*scalar;
	}
}
namespace algebra{
	template<class OperatorT>
	struct mult_operation_t{
		static constexpr auto apply(auto const& a, auto const& b){
			return OperatorT::apply(a,b);
		}
		//operation with scalar
		static constexpr auto apply(vector::scalar_wrapper_t<auto> const& a, vector::basis_vector_t<auto,auto> const& b){
			return vector::basis_vector(b.element, apply(a.value,b.coordinate));
		}
		static constexpr auto apply(vector::Scalar const& a, vector::basis_vector_t<auto,auto> const& b){
			return vector::basis_vector(b.element, a*b.coordinate);
		}
		static constexpr auto apply(vector::basis_vector_t<auto,auto> const& a, vector::Scalar const& b){
			return apply(b,a);
		}
		//operation with zero
		static constexpr auto apply(vector::zero_t zero_, auto const&){
			return zero_;
		}
		static constexpr auto apply(vector::basis_vector_t<auto,auto> const&, vector::zero_t zero_){
			return zero_;
		}
		//operation with basis vectors
		template<class ElementT1, class ElementT2> 
		static constexpr auto apply(vector::basis_vector_t<ElementT1,auto> const& a, vector::basis_vector_t<ElementT2,auto> const& b){
			return vector::basis_vector(apply(a.element, b.element), apply(a.coordinate, b.coordinate));
		}
		//develop product over addition
		static constexpr auto apply(auto const& a, group::generated_by_operation_t<vector::add_operation_t, auto,auto> const& b){
			return apply(a,b.first)+apply(a,b.second);
		}
		template<class B> requires !group::Operation<vector::add_operation_t, B>
		static constexpr auto apply(group::generated_by_operation_t<vector::add_operation_t, auto,auto> const& a, B const& b){
			return apply(a.first,b)+apply(a.second,b);
		}

		static constexpr auto inverse(vector::Scalar const& a){return symbolic::integer<1>/a;}
		static constexpr auto inverse(vector::scalar_wrapper_t<auto> const& a){
			return vector::scalar_wrapper_t{inverse(a.value)};
		}
		static constexpr auto inverse(vector::basis_vector_t<auto,auto> const& a){
			using symbolic::inverse;
			return vector::basis_vector(OperatorT::inverse(a.element),inverse(a.coordinate));
		}
	};
}

#endif /* ALGEBRA_MULTIPLICATION_H */
