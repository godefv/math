#ifndef EXPRESSION_H
#define EXPRESSION_H 

#include"group/operation.h"
#include"group/power.h"
#include"group/identity.h"
#include"symbolic/symbol.h"
#include"scalar.h"

namespace godefv::math{
	template<class T> concept Expression=Scalar<T> || Symbol<T> || group::GeneratedByAnyOperation<T>;
	template<class T> concept NonSimpleScalarExpression=NonSimpleScalar<T> && Expression<T>;
}

#endif /* EXPRESSION_H */
