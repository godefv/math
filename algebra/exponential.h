#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H 

#include"../vector/basis.h"
#include"../group/identity.h"

#include<cmath>
#include<limits>

namespace algebra{
	constexpr auto exp(auto const& a){
		using namespace algebra::geometric;
		using namespace algebra::geometric::operators;
		vector::basis_element_t<group::identity_t<auto>, auto> square=project(a*a, grades<0>());
		using ScalarT=decltype(square.coordinate);
		auto constexpr one=vector::basis_element_t{decltype(square.element){}, static_cast<ScalarT>(1.0)};

		auto angle=std::sqrt(std::abs(square.coordinate));
		if(angle<=std::numeric_limits<ScalarT>::epsilon()*10){
			return one+a;
		}
		auto normalized_a=a/angle;
		if(square.coordinate>0){
			return std::cosh(angle)*one+std::sinh(angle)*normalized_a;
		}else{
			return std::cos(angle)*one+std::sin(angle)*normalized_a;
		}
	}
}

#endif /* EXPONENTIAL_H */
