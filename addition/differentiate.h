#ifndef ADDITION_DIFFERENTIATE_H
#define ADDITION_DIFFERENTIATE_H 

#include"operation.h"
#include"../differentiate.h"
#include"../group/morphism.h"

namespace godefv::math{
	Symbol{SymbolT}
	auto constexpr differentiate(SymbolT, group::Generated<add_operation_t> const& operand){
		auto constexpr morphism=group::endomorphism(add_operation_t{}, [](auto const& x){return differentiate(SymbolT{}, x);});
		return morphism(operand);
	}
}

#endif /* ADDITION_DIFFERENTIATE_H */
