#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H 

#include"../vector/basis.h"
#include"../group/identity.h"
#include"../symbolic/trigonometry.h"
#include"../symbolic/rational.h"
#include"../eval.h"

#include<cmath>
#include<limits>

namespace algebra{
	template<class OneElementT>
	constexpr auto exp(auto const& a){
		using namespace algebra::geometric::operators;
		auto constexpr one=vector::unit_t<OneElementT>{};

		if constexpr(std::is_same<decltype(a*a),vector::zero_t>::value){
			return one+a;
		}else{
			vector::basis_vector_t<OneElementT, auto> square=a*a;

			using std::sqrt;
			using std::abs;
			auto angle=sqrt(abs(square.coordinate));
			double angle_value=eval(angle);
			if(angle_value<=std::numeric_limits<double>::epsilon()*10){
				return 1.*one+1.*a;
			}
			auto normalized_a=a/angle_value;
			if(eval(square.coordinate)>0){
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
