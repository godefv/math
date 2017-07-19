#ifndef INVERSE_H
#define INVERSE_H 

#include"identity.h"

namespace group{
	//inverse generates a new type by default
	template<class Operator, class T> struct generated_inverse_t{T value;};

	template<class Operator, class A>
	constexpr auto inverse(A const& a){return generated_inverse_t<Operator, A>{a};}
	template<class Operator, class T> struct inverse_impl_t{using type=decltype(inverse<Operator>(T{}));};
	//inverse of inverse is self
	template<class Operator, class T> struct inverse_impl_t<Operator, generated_inverse_t<Operator, T>>{using type=T;};
	//inverse of identity is identity
	template<class Operator> struct inverse_impl_t<Operator, identity_t<Operator>>{using type=identity_t<Operator>;};

	template<class Operator, class T> using inverse_t=typename inverse_impl_t<Operator, T>::type;

	template<class ElementT, class IdentityT, class OperatorT, template<class A> class InverseT>
	concept bool HasInverse=std::is_same<InverseT<InverseT<ElementT>>, ElementT>::value
	                     && std::is_same<decltype(OperatorT::template apply(InverseT<ElementT>{},ElementT{})), IdentityT>::value
	                     && std::is_same<decltype(OperatorT::template apply(ElementT{},InverseT<ElementT>{})), IdentityT>::value
	                     && AbsorbsIdentityElement<InverseT<ElementT>,IdentityT,OperatorT>
                         ;
} 

#endif /* INVERSE_H */
