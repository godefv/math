#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H 

#include"../vector/basis.h"
#include"../group/identity.h"
#include"../symbolic/trigonometry.h"
#include"../symbolic/rational.h"
#include"../symbolic/eval.h"

#include<cmath>
#include<limits>

namespace algebra{
	template<class OneElementT>
	constexpr auto exp(auto const& a){
		using namespace algebra::geometric;
		using namespace algebra::geometric::operators;
		auto constexpr one=vector::basis_element_t{OneElementT{}, symbolic::integer<1>};

		if constexpr(std::is_same<decltype(project(a*a, grades<0>())),vector::zero_t>::value){
			return one+a;
		}else{
			vector::basis_element_t<OneElementT, auto> square=project(a*a, grades<0>());
			double square_scalar=eval(square.coordinate);

			auto angle=std::sqrt(std::abs(square_scalar));
			if(angle<=std::numeric_limits<double>::epsilon()*10){
				return 1.*one+a;
			}
			auto normalized_a=a/angle;
			if(square_scalar>0){
				return std::cosh(angle)*one+std::sinh(angle)*normalized_a;
			}else{
				return std::cos(angle)*one+std::sin(angle)*normalized_a;
				//using std::cosh;
				//using std::sinh;
				//return cosh(angle)*one+sinh(angle)*normalized_a;
			//}else{
				//using std::cos;
				//using std::sin;
				//return cos(angle)*one+sin(angle)*normalized_a;
			}
		}
	}
}

#endif /* EXPONENTIAL_H */
