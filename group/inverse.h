#ifndef GROUP_INVERSE_H
#define GROUP_INVERSE_H 

#include"power.h"
#include"identity.h"

namespace godefv::math::group{
	//inverse is power<-1>
	template<class OperatorT>
	auto constexpr inverse(OperatorT, auto const& operand){
		return power(OperatorT{} ,integer<-1>, operand);
	}

	template<class OperatorT, class T> using inverse_t=decltype(inverse(OperatorT{}, T{}));

	template<class ElementT, class IdentityT, class OperatorT, template<class A> class InverseT>
	concept bool HasInverse=std::is_same<InverseT<InverseT<ElementT>>, ElementT>::value
	                     && std::is_same<decltype(OperatorT::apply(InverseT<ElementT>{},ElementT{})), IdentityT>::value
	                     && std::is_same<decltype(OperatorT::apply(ElementT{},InverseT<ElementT>{})), IdentityT>::value
	                     && AbsorbsIdentityElement<InverseT<ElementT>,IdentityT,OperatorT>
                         ;
} 

#endif /* GROUP_INVERSE_H */
