#ifndef SYMBOLIC_UNIT_TEST_H
#define SYMBOLIC_UNIT_TEST_H 

#include"symbol.h"
#include"../unit_test.h"
#include<iostream>

template<char> struct symbol_name_t{};
using x_t=symbolic::symbol_t<symbol_name_t<'x'>>; 
using y_t=symbolic::symbol_t<symbol_name_t<'y'>>; 
x_t x;
y_t y;
template<char Name> std::ostream& operator<<(std::ostream& out,symbolic::symbol_t<symbol_name_t<Name>>){return out<<Name;}

template<char C1, char C2>
int constexpr static_compare(symbolic::symbol_t<symbol_name_t<C1>>, symbolic::symbol_t<symbol_name_t<C2>>){
	return C2-C1;
}

#endif /* SYMBOLIC_UNIT_TEST_H */
