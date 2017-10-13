#ifndef SYMBOLIC_EXPONENTIAL_H
#define SYMBOLIC_EXPONENTIAL_H 

#include"factorial.h"
#include"rational.h"

#include<boost/hana.hpp>
#include<cmath>

namespace symbolic{
	auto constexpr exp(RatioLessThanOne a){
		namespace hana=boost::hana;
		using namespace hana::literals;
		return hana::fold(std::make_index_sequence<11>{}, hana::make_tuple(integer<0>, integer<1>, integer<1>, integer<1>), [a](auto result_exp_fact, auto){
				return hana::make_tuple(result_exp_fact[0_c]+result_exp_fact[1_c]/result_exp_fact[2_c], result_exp_fact[1_c]*a, result_exp_fact[2_c]*result_exp_fact[3_c], result_exp_fact[3_c]+integer<1>);
		})[0_c];
	}
}

#endif /* SYMBOLIC_EXPONENTIAL_H */
