#ifndef INVERSE_H
#define INVERSE_H 

#include"identity.h"

namespace group{
	//inverse generates a new type by default
	template<class Operator, class T> struct generated_inverse_t{
		Operator operation;
		T value_before_inverse;
	};

	template<class Operator, class A>
	constexpr auto inverse(A const& a){return generated_inverse_t<Operator, A>{Operator{}, a};}
	//inverse of inverse is self
	template<class Operator, class A>
	constexpr auto inverse(generated_inverse_t<Operator, A> const& a){return a.value_before_inverse;}
	//inverse of identity is identity
	template<class Operator>
	constexpr auto inverse(identity_t<Operator> const& a){return a;}

	template<class Operator, class T> using inverse_t=decltype(Operator::inverse(T{}));

	template<class ElementT, class IdentityT, class OperatorT, template<class A> class InverseT>
	concept bool HasInverse=std::is_same<InverseT<InverseT<ElementT>>, ElementT>::value
	                     && std::is_same<decltype(OperatorT::apply(InverseT<ElementT>{},ElementT{})), IdentityT>::value
	                     && std::is_same<decltype(OperatorT::apply(ElementT{},InverseT<ElementT>{})), IdentityT>::value
	                     && AbsorbsIdentityElement<InverseT<ElementT>,IdentityT,OperatorT>
                         ;

	template<class Operator, class T>
	bool constexpr operator==(generated_inverse_t<Operator, T> const& a, generated_inverse_t<Operator, T> const& b){
		return a.value_before_inverse==b.value_before_inverse;
	}
	template<class Operator, class T>
	bool constexpr operator!=(generated_inverse_t<Operator, T> const& a, generated_inverse_t<Operator, T> const& b){
		return !(a==b);
	}

} 

#endif /* INVERSE_H */
