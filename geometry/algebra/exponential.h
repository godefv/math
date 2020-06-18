#ifndef GEOMETRY_ALGEBRA_EXPONENTIAL_H
#define GEOMETRY_ALGEBRA_EXPONENTIAL_H 

#include"geometric_product.h"
#include"norm.h"
#include"../../symbolic/operation/trigonometry.h"

namespace godefv::math::geometry{
	template<KBlade<2> BivectorT> 
	requires Zero<decltype(square(BivectorT{}))>
	constexpr auto exp(BivectorT const& a){
			return one+a;
	}

	template<KBlade<2> BivectorT> 
	requires (PositiveScalar<decltype(square(BivectorT{}))>
			&& !Zero<decltype(square(BivectorT{}))>
	)
	constexpr auto exp(BivectorT const& a){
		Scalar auto angle=norm(a);
		using std::cosh;
		using std::sinh;
		return cosh(angle)+sinh(angle)*(a/angle);
	}

	template<KBlade<2> BivectorT> 
	requires (PositiveScalar<decltype(-square(BivectorT{}))>
			&& !Zero<decltype(square(BivectorT{}))>
	)
	constexpr auto exp(BivectorT const& a){
		Scalar auto angle=norm(a);
		using std::cos;
		using std::sin;
		return cos(angle)+sin(angle)*(a/angle);
	}

	template<KVector<2> BivectorT> 
	requires (Scalar<decltype(square(BivectorT{}))>
			&& !PositiveScalar<decltype(square(BivectorT{}))>
			&& !PositiveScalar<decltype(-square(BivectorT{}))>
	)
	constexpr auto exp(BivectorT const& a){
		using godefv::math::eval;
		double square=eval(a|a);
		if(square==0){
			return 1.+eval(a);
		}
		double angle=std::sqrt(std::abs(square));
		if(square>0){
			using std::cosh;
			using std::sinh;
			return eval(cosh(angle)+sinh(angle)*(a/angle));
		}
		{
			using std::cos;
			using std::sin;
			return eval(cos(angle)+sin(angle)*(a/angle));
		}
	}
}

#endif /* GEOMETRY_ALGEBRA_EXPONENTIAL_H */
