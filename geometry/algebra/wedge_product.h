#ifndef GEOMETRY_ALGEBRA_WEDGE_PRODUCT_H
#define GEOMETRY_ALGEBRA_WEDGE_PRODUCT_H 

#include"geometric_product.h"
#include"grade.h"
#include"../../multiplication/operation.h"

#include<cmath>

namespace godefv::math::geometry{
	struct wedge_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a^b;
		}
		auto constexpr operator()(auto const& a, auto const& b) const{
			return std::decay_t<decltype(*this)>::apply(a,b);
		}
	};
	using bilinear_wedge_operation_t=bilinear_operation_t<wedge_operation_t>;

	//by default, use group operations
	auto constexpr operator^(auto const& a, auto const& b){
		return bilinear_operation_t<wedge_operation_t>::apply(a,b);
	}

	template<Blade Blade1, Blade Blade2>
	auto constexpr operator^(Blade1 const& a, Blade2 const& b){
		return project(a*b, grades<grade(Blade1{})+grade(Blade2{})>());
	}
}


#endif /* GEOMETRY_ALGEBRA_WEDGE_PRODUCT_H */
