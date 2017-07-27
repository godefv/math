#ifndef ALGEBRA_FORMATTING_H
#define ALGEBRA_FORMATTING_H 

#include<iostream>

namespace algebra{
	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	std::ostream& operator<<(std::ostream& out, group::generated_element_t<add_operation_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT>, auto, auto> const& ab){
		return out<<"("<<ab.first<<") + ("<<ab.second<<")";
	}
}

#endif /* ALGEBRA_FORMATTING_H */
