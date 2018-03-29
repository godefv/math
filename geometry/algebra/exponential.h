#ifndef GEOMETRY_ALGEBRA_EXPONENTIAL_H
#define GEOMETRY_ALGEBRA_EXPONENTIAL_H 

#include"definition.h"
#include"grade.h"
#include"norm.h"
#include"../../symbolic/trigonometry.h"

namespace math::geometry{
	template<KBlade<2> BivectorT> 
		requires Symbol<BivectorT> && std::is_same<decltype(BivectorT{}*BivectorT{}),zero_t>::value 
	constexpr auto exp(BivectorT const& a){
			return one+a;
	}

	template<KBlade<2> BivectorT> 
		requires Symbol<BivectorT> && !std::is_same<decltype(BivectorT{}*BivectorT{}),zero_t>::value 
			  && eval(BivectorT{}*BivectorT{})>0
	constexpr auto exp(BivectorT const& a){
		Scalar angle=norm(a);
		using std::cosh;
		using std::sinh;
		return cosh(angle)+sinh(angle)*(a/angle);
	}

	template<KBlade<2> BivectorT> 
		requires Symbol<BivectorT> && !std::is_same<decltype(BivectorT{}*BivectorT{}),zero_t>::value 
			  && eval(BivectorT{}*BivectorT{})<0
	constexpr auto exp(BivectorT const& a){
		Scalar angle=norm(a);
		using std::cos;
		using std::sin;
		return cos(angle)+sin(angle)*(a/angle);
	}
}

#endif /* GEOMETRY_ALGEBRA_EXPONENTIAL_H */
