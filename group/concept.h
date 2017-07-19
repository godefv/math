#ifndef CONCEPT_H
#define CONCEPT_H 

#include"apply_operation.h"
#include"identity.h"
#include"inverse.h"

#include<boost/hana.hpp>

namespace group{
	namespace hana=boost::hana;

	template<class TypeSetT, class T>
	constexpr bool is_in_type_list(T const& a){
		return static_cast<bool>(hana::is_just(hana::find(TypeSetT{}, a)));
	}

	template<class GroupT, class ElementT, class IdentityT, class OperatorT, template<class> class InverseT>
	concept bool GroupElement=
		   group::AbsorbsIdentityElement<ElementT, IdentityT, OperatorT> 
		&& group::HasInverse            <ElementT, IdentityT, OperatorT, InverseT> 
		&& is_in_type_list<GroupT>(hana::type_c<ElementT>)
		&& is_in_type_list<GroupT>(hana::type_c<InverseT<ElementT>>)
		&& static_cast<bool>(hana::all(hana::transform(GroupT{}, [&](auto const& g){
				return is_in_type_list<GroupT>(hana::type_c<decltype(apply_operation<OperatorT>(ElementT{},typename std::decay_t<decltype(g)>::type{}))>);
		})))
	;

	template<class GroupT, class IdentityT, class OperatorT, template<class> class InverseT>
	concept bool Group=static_cast<bool>(hana::all(hana::transform(GroupT{}, [&](auto const& g){
			return GroupElement<GroupT, typename std::decay_t<decltype(g)>::type, IdentityT, OperatorT, InverseT>;
		})));
}

#endif /* CONCEPT_H */
