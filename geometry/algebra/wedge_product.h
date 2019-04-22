#ifndef GEOMETRY_ALGEBRA_WEDGE_PRODUCT_H
#define GEOMETRY_ALGEBRA_WEDGE_PRODUCT_H 

#include"geometric_product.h"
#include"../../multiplication/operation.h"

#include<cmath>

namespace godefv::math::geometry{
	struct wedge_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a^b;
		}
	};
	using bilinear_wedge_operation_t=bilinear_operation_t<wedge_operation_t>;

	//by default, use group operations
	auto constexpr operator^(auto const& a, auto const& b){
		return bilinear_operation_t<wedge_operation_t>::apply(a,b);
	}

	Blade{Blade2}
	auto constexpr operator^(Blade const& a, Blade2 const& b){
		return project(a*b, grades<grade(a)+grade(b)>());
	}
}


#endif /* GEOMETRY_ALGEBRA_WEDGE_PRODUCT_H */
