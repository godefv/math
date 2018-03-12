#ifndef SYMBOLIC_VECTOR_H
#define SYMBOLIC_VECTOR_H 

#include"symbol.h"
#include"../vector/basis.h"
#include"../vector/addition.h"

namespace symbolic{
	template<Symbol ElementT, Symbol ScalarT>
	struct is_symbol<vector::basis_vector_t<ElementT, ScalarT>>: std::true_type{};
}

#endif /* SYMBOLIC_VECTOR_H */
