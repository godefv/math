#ifndef ALGEBRA_GEOMETRIC_H
#define ALGEBRA_GEOMETRIC_H 

#include"../group/geometric.h"
#include"../group/ordering.h"
#include"../vector/addition.h"
#include"../symbolic/trigonometry.h"
#include"../symbolic/rational.h"
#include"../inverse.h"
#include"multiplication.h"

#include<boost/hana.hpp>
#include<cmath>

namespace algebra::geometric{

	template<class BivectorT> 
		requires boost::hana::value(grades(BivectorT{})==grades<2>()) 
		      && symbolic::Angle<decltype(BivectorT{}.coordinate)> 
		      && symbolic::Ratio<decltype(BivectorT{}.coordinate.coordinate)> 
		      && std::is_same<decltype(BivectorT{}*BivectorT{}),vector::zero_t>::value 
	constexpr auto exp(BivectorT const& a){
			return one+a;
	}

	template<class BivectorT> 
		requires boost::hana::value(grades(BivectorT{})==grades<2>()) 
		      && symbolic::Angle<decltype(BivectorT{}.coordinate)> 
		      && symbolic::Ratio<decltype(BivectorT{}.coordinate.coordinate)> 
		      && !std::is_same<decltype(BivectorT{}*BivectorT{}),vector::zero_t>::value
			  && eval((BivectorT{}*BivectorT{}).coordinate)>0
	constexpr auto exp(BivectorT const& a){
		using namespace operators;
		vector::basis_vector_t<group::geometric::one_t, auto> square=a*a;
		using std::sqrt;
		using std::abs;
		auto angle=sqrt(abs(square.coordinate));
		using std::cosh;
		using std::sinh;
		return vector::scalar_wrapper_t{vector::unit(cosh(angle))}*one
		      +vector::scalar_wrapper_t{vector::unit(sinh(angle))}*(a/vector::scalar_wrapper_t{angle});
	}

	template<class BivectorT> 
		requires boost::hana::value(grades(BivectorT{})==grades<2>()) 
		      && symbolic::Angle<decltype(BivectorT{}.coordinate)> 
		      && symbolic::Ratio<decltype(BivectorT{}.coordinate.coordinate)> 
		      && !std::is_same<decltype(BivectorT{}*BivectorT{}),vector::zero_t>::value
			  && eval((BivectorT{}*BivectorT{}).coordinate)<0
	constexpr auto exp(BivectorT const& a){
		using namespace operators;
		vector::basis_vector_t<group::geometric::one_t, auto> square=a*a;
		using std::sqrt;
		using std::abs;
		auto angle=sqrt(abs(square.coordinate));
		using std::cos;
		using std::sin;
		return vector::scalar_wrapper_t{vector::unit(cos(angle))}*one
		      +vector::scalar_wrapper_t{vector::unit(sin(angle))}*(a/vector::scalar_wrapper_t{angle});
	}
}

#endif /* ALGEBRA_GEOMETRIC_H */
