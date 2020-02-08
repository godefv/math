#ifndef SYMBOLIC_CONSTANT_H
#define SYMBOLIC_CONSTANT_H 

#include"symbol.h"
#include"../scalar.h"

#include<limits>

namespace godefv::math{
	auto constexpr infinity="infinity"_symbol;
	using infinity_t=std::decay_t<decltype(infinity)>;
	auto constexpr eval_with_data(infinity_t, auto const&){return std::numeric_limits<double>::infinity();}
	template<> struct is_scalar<infinity_t>:std::true_type {};

	auto constexpr pi="π"_symbol;
	using pi_t=std::decay_t<decltype(pi)>;
	auto constexpr eval_with_data(pi_t, auto const&){return 3.14159265358979323846;}
	template<> struct is_scalar<pi_t>:std::true_type {};

}

#endif /* SYMBOLIC_CONSTANT_H */
