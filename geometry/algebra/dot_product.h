#ifndef GEOMETRY_ALGEBRA_DOT_PRODUCT_H
#define GEOMETRY_ALGEBRA_DOT_PRODUCT_H 

#include"geometric_product.h"
#include"../../multiplication/operation.h"
#include"../../abs.h"

#include<cmath>

namespace godefv::math::geometry{
	struct dot_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a|b;
		}
	};
	using bilinear_dot_operation_t=bilinear_operation_t<dot_operation_t>;

	//operation on blades
	Blade{Blade2}
	auto constexpr operator|(Blade const& a, Blade2 const& b){
		return project(a*b, grades<abs(grade(a)-grade(b))>());
	}
	//extand operation by bilinearity
	template<MultiVector A, MultiVector B> 
		requires !(Blade<A> && Blade<B>)
	auto constexpr operator|(A const& a, B const& b){
		return bilinear_operation_t<dot_operation_t>::apply(a,b);
	}

}

#endif /* GEOMETRY_ALGEBRA_DOT_PRODUCT_H */
