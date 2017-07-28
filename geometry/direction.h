#ifndef GEOMETRY_DIRECTION_H
#define GEOMETRY_DIRECTION_H 

#include<type_traits>

namespace geometry{
	template<int> struct direction_t{};

	template<int i> constexpr int index(direction_t<i>){return i;}

	template<int ia, int ib>
	constexpr bool is_sorted(direction_t<ia> const& A, direction_t<ib> const& B){return ia<ib;}
}

#endif /* GEOMETRY_DIRECTION_H */
