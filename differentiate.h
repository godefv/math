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

	auto constexpr differentiate(symbol_t<auto>, SimpleScalar){
		return integer<0>;
	}
	auto constexpr differentiate(symbol_t<auto>, symbol_t<auto>){
		return integer<0>;
	}
}

#endif /* DIFFERENTIATE_H */
