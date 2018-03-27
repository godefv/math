#ifndef GEOMETRY_ALGEBRA_NORM_H
#define GEOMETRY_ALGEBRA_NORM_H 

#include"definition.h"
#include"dot_product.h"
#include"../../symbolic/operation/all.h"
#include"../../scalar.h"

#include<cmath>

namespace math::geometry{
	auto constexpr norm(MultiVector const& a){
		Scalar a_square=(a|a);
		using std::sqrt;
		using std::abs;
		return sqrt(abs(a_square));
	}

	auto constexpr normalized(auto const& a){
		return a/norm(a);
	}
}

#endif /* GEOMETRY_ALGEBRA_NORM_H */
