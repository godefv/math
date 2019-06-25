#ifndef EVAL_H
#define EVAL_H 

#include"hana.h"

namespace godefv::math{
	auto constexpr eval_with_data(auto const& a, auto const&){return a;}

	auto constexpr eval(auto const& a){return eval_with_data(a, boost::hana::nothing);}
}

#endif /* EVAL_H */
