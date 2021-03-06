#ifndef SYMBOLIC_UNIT_TEST_H
#define SYMBOLIC_UNIT_TEST_H 

#include"symbol.h"
#include"../unit_test.h"
#include"../scalar.h"

namespace math=godefv::math;

using x_t=math::symbol_t<math::name_t<'x'>>; 
using y_t=math::symbol_t<math::name_t<'y'>>; 
using z_t=math::symbol_t<math::name_t<'z'>>; 
using k_t=math::symbol_t<math::name_t<'k'>>; 
using l_t=math::symbol_t<math::name_t<'l'>>; 
using m_t=math::symbol_t<math::name_t<'m'>>; 
using n_t=math::symbol_t<math::name_t<'n'>>; 
x_t x;
y_t y;
z_t z;
k_t k;
l_t l;
m_t m;
n_t n;

namespace godefv::math{
	template<> struct is_scalar<k_t>:std::true_type {};
	template<> struct is_scalar<l_t>:std::true_type {};
	template<> struct is_scalar<m_t>:std::true_type {};
	template<> struct is_scalar<n_t>:std::true_type {};
}

auto constexpr eval_symbol(x_t){return 8.0;}
auto constexpr eval_symbol(y_t){return 3.0;}
auto constexpr eval_symbol(z_t){return 1.0;}
auto constexpr eval_symbol(k_t){return 8;}
auto constexpr eval_symbol(l_t){return 3;}
auto constexpr eval_symbol(m_t){return 1;}

#endif /* SYMBOLIC_UNIT_TEST_H */
