#ifndef SYMBOLIC_CONSTANT_H
#define SYMBOLIC_CONSTANT_H 

#include"symbol.h"
#include"../scalar.h"

#include<limits>

namespace math{
	auto constexpr infinity="infinity"_symbol;
	using infinity_t=std::decay_t<decltype(infinity)>;
	auto constexpr eval(infinity_t){return std::numeric_limits<double>::infinity();}
	auto constexpr abs(infinity_t const& a){return a;}
	template<> struct is_scalar<infinity_t>:std::true_type {};

	auto constexpr pi="π"_symbol;
	using pi_t=std::decay_t<decltype(pi)>;
	auto constexpr eval(pi_t){return 3.14159265358979323846;}
	auto constexpr abs(pi_t const& a){return a;}
	template<> struct is_scalar<pi_t>:std::true_type {};

}

#endif /* SYMBOLIC_CONSTANT_H */
