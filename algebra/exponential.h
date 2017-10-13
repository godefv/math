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
			auto square_scalar=square.coordinate;

			using std::sqrt;
			using std::abs;
			auto angle=sqrt(abs(square_scalar));
			double angle_value=eval(angle);
			if(angle_value<=std::numeric_limits<double>::epsilon()*10){
				return 1.*one+1.*a;
			}
			auto normalized_a=a/angle_value;
			if(eval(square_scalar)>0){
				using std::cosh;
				using std::sinh;
				return eval(cosh(angle))*one+eval(sinh(angle))*normalized_a;
			}else{
				using std::cos;
				using std::sin;
				return eval(cos(angle))*one+eval(sin(angle))*normalized_a;
			}
		}
	}
}

#endif /* EXPONENTIAL_H */
