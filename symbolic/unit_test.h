#ifndef SYMBOLIC_UNIT_TEST_H
#define SYMBOLIC_UNIT_TEST_H 

#include"symbol.h"
#include"../unit_test.h"
#include<iostream>

using x_t=math::symbol_t<math::symbol_name_t<'x'>>; 
using y_t=math::symbol_t<math::symbol_name_t<'y'>>; 
using z_t=math::symbol_t<math::symbol_name_t<'z'>>; 
x_t x;
y_t y;
z_t z;

#endif /* SYMBOLIC_UNIT_TEST_H */
