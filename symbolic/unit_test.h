#ifndef SYMBOLIC_UNIT_TEST_H
#define SYMBOLIC_UNIT_TEST_H 

#include"symbol.h"
#include"../unit_test.h"
#include<iostream>

using x_t=symbolic::symbol_t<struct x_symbol_name_t>; 
x_t x;
inline bool operator==(x_t,x_t){return true;}
inline bool operator!=(x_t,x_t){return false;}
inline std::ostream& operator<<(std::ostream& out,x_t){return out<<"x";}

#endif /* SYMBOLIC_UNIT_TEST_H */
