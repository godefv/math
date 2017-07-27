#ifndef ALGEBRA_GEOMETRIC_H
#define ALGEBRA_GEOMETRIC_H 

#include"addition.h"
#include"multiplication.h"
#include"../group/geometric.h"

namespace algebra::geometric{
	template<class GroupT, vector::Scalar ScalarT=double> 
	using  add_operation_t=algebra:: add_operation_t<GroupT, group::geometric::one_t, group::geometric::mult_operation_t, group::geometric::inverse_t, ScalarT>;
	template<class GroupT, vector::Scalar ScalarT=double> 
	using mult_operation_t=algebra::mult_operation_t<GroupT, group::geometric::one_t, group::geometric::mult_operation_t, group::geometric::inverse_t, ScalarT>;

}

#endif /* ALGEBRA_GEOMETRIC_H */
