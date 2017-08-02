#ifndef GEOMETRY_DIRECTION_H
#define GEOMETRY_DIRECTION_H 

#include<type_traits>

namespace geometry{
	template<int> struct direction_t{};

	template<int i> constexpr int index(direction_t<i>){return i;}

	template<int ia, int ib>
	constexpr int static_compare(direction_t<ia> const& A, direction_t<ib> const& B){return ib-ia;}

	template<int i>
	bool constexpr operator==(direction_t<i> const&, direction_t<i> const&){
		return true;
	}
	template<int i>
	bool constexpr operator!=(direction_t<i> const& a, direction_t<i> const& b){
		return !(a==b);
	}

}

#endif /* GEOMETRY_DIRECTION_H */
