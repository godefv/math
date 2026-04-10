#ifndef DIFFERENTIATE_H
#define DIFFERENTIATE_H 

#include"symbolic/symbol.h"
#include"symbolic/rational.h"
#include"scalar.h"

namespace godefv::math{
	template<class Name>
	auto constexpr differentiate(symbol_t<Name>, symbol_t<Name>){
		return integer<1>;
	}

	template<class Name>
	auto constexpr differentiate(symbol_t<Name>, SimpleScalar auto){
		return integer<0>;
	}
	template<class Name1, class Name2>
	auto constexpr differentiate(symbol_t<Name1>, symbol_t<Name2>){
		return integer<0>;
	}
}

#endif /* DIFFERENTIATE_H */
