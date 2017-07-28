#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H 

#include"../vector/basis.h"
#include"../group/identity.h"

#include<cmath>
#include<limits>

namespace algebra{
	constexpr auto exp(auto const& a){
		vector::basis_element_t<group::identity_t<auto>, auto> square=(a*a);
		auto angle=std::sqrt(std::abs(square.coordinate));
		using ScalarT=decltype(angle);
		auto constexpr one=decltype(square){static_cast<ScalarT>(1.0)};
		if(angle<std::numeric_limits<ScalarT>::epsilon()*10){
			return one+a;
		}
		auto normalized_a=a*(1./angle);
		if(square.coordinate>0){
			return std::cosh(angle)*one+std::sinh(angle)*normalized_a;
		}else{
			return std::cos(angle)*one+std::sin(angle)*normalized_a;
		}
	}
}

#endif /* EXPONENTIAL_H */
