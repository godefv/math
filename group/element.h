#ifndef ELEMENT_H
#define ELEMENT_H 

template <class T, class U> concept bool Same = std::is_same<T,U>::value;

template<class ElementT, class IdentityT, class BinaryOperatorT>
concept bool AbsorbsIdentityElement=requires(ElementT a, BinaryOperatorT op, IdentityT identity){
	requires Same<decltype(op(a,identity)),ElementT;>
	requires Same<decltype(op(identity,a)),ElementT;>
};

template<class ElementT, class IdentityT, class BinaryOperatorT, class InverseOperatorT>
concept bool AbsorbsIdentityElementAndHasInverse=requires(ElementT a, BinaryOperatorT op, IdentityT identity, InverseOperatorT inverse){
	inverse(a);
	requires AbsorbsIdentityElement<ElementT,IdentityT,BinaryOperatorT>;
	requires AbsorbsIdentityElement<decltype(inverse(a)),IdentityT,BinaryOperatorT>;
	requires Same<decltype(inverse(inverse(a))),ElementT;>
	requires Same<decltype(op(inverse(a),a)),IdentityT;>
	requires Same<decltype(op(a,inverse(a))),IdentityT;>
};

/*
template<class ElementT, class IdentityT, template<class A, class B> class OperatorT>
concept bool AbsorbsIdentityElement=Same<OperatorT<ElementT,IdentityT>, ElementT>
                                 && Same<OperatorT<IdentityT,ElementT>, ElementT>
								 ;

template<class ElementT, class IdentityT, template<class A, class B> class OperatorT, template<class A> class InverseT>
concept bool AbsorbsIdentityElementAndHasInverse=
	AbsorbsIdentityElement<ElementT          ,IdentityT,OperatorT>
&&	AbsorbsIdentityElement<InverseT<ElementT>,IdentityT,OperatorT>

&&	Same<InverseT<InverseT<ElementT>>, ElementT>
	
&&	Same<OperatorT<InverseT<ElementT>,ElementT>, IdentityT>
&&	Same<OperatorT<ElementT,InverseT<ElementT>>, IdentityT>
;
*/

//template<class ElementT, class IdentityT, class BinaryOperatorT, class InverseOperatorT>
//concept bool GroupElement=requires(){
	//requires AbsorbsIdentityElementAndHasInverse<ElementT,IdentityT,BinaryOperatorT,InverseOperatorT>;
//};

#endif /* ELEMENT_H */
