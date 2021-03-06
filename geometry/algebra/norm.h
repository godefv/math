#ifndef GEOMETRY_ALGEBRA_NORM_H
#define GEOMETRY_ALGEBRA_NORM_H 

#include"definition.h"
#include"dot_product.h"
#include"../../symbolic/operation/all.h"
#include"../../scalar.h"

#include<cmath>

namespace godefv::math::geometry{
	auto constexpr norm(MultiVector auto const& a){
		Scalar auto a_square=(a|a);
		using std::sqrt;
		using std::abs;
		return sqrt(abs(a_square));
	}

	template<class T> requires NonZero<decltype(norm(T{}))>
	auto constexpr normalized(T const& a){
		return a/norm(a);
	}
}

#endif /* GEOMETRY_ALGEBRA_NORM_H */
