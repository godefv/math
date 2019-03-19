#ifndef EXPRESSION_H
#define EXPRESSION_H 

#include"group/operation.h"
#include"group/power.h"
#include"group/identity.h"
#include"symbolic/symbol.h"
#include"scalar.h"

namespace math{
	template<class T> concept bool Expression=Scalar<T> || Symbol<T> || group::GeneratedByAnyOperation<T>;
	template<class T> concept bool NonSimpleScalarExpression=!SimpleScalar<T> && Expression<T>;
}

#endif /* EXPRESSION_H */
