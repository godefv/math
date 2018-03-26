#ifndef GEOMETRY_ALGEBRA_DOT_PRODUCT_H
#define GEOMETRY_ALGEBRA_DOT_PRODUCT_H 

#include"grade.h"
#include"../../multiplication/operation.h"
#include"../../abs.h"

#include<cmath>

namespace math::geometry{
	struct dot_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a|b;
		}
	};
	using bilinear_dot_operation_t=bilinear_operation_t<dot_operation_t>;

	//by default, use group operations
	auto constexpr operator|(auto const& a, auto const& b){
		return bilinear_operation_t<dot_operation_t>::apply(a,b);
	}

	Blade{Blade2}
	auto constexpr operator|(Blade const& a, Blade2 const& b){
		return project(a*b, grades<abs(grade(a)-grade(b))>());
	}
}

#endif /* GEOMETRY_ALGEBRA_DOT_PRODUCT_H */
