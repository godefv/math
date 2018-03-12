#ifndef GROUP_REVERSE_H
#define GROUP_REVERSE_H 

#include"operation.h"

namespace group{
	constexpr auto reverse(auto const& a){return a;}

	template<class OperatorT, class A,class B> 
	constexpr auto reverse(group::generated_by_operation_t<OperatorT, A,B> const& ab){
		return OperatorT::apply(reverse(ab.second), reverse(ab.first));
	}
}

#endif /* GROUP_REVERSE_H */
