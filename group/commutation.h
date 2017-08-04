#ifndef GROUP_COMMUTATION_H
#define GROUP_COMMUTATION_H 

#include"ordering.h"

namespace group{
	template<int> struct indexed_element_t{};

	template<int i> constexpr int index(indexed_element_t<i>){return i;}

	template<int ia, int ib>
	constexpr int static_compare(indexed_element_t<ia> const& A, indexed_element_t<ib> const& B){return ib-ia;}

	template<int i>
	bool constexpr operator==(indexed_element_t<i> const&, indexed_element_t<i> const&){
		return true;
	}
	template<int i>
	bool constexpr operator!=(indexed_element_t<i> const& a, indexed_element_t<i> const& b){
		return !(a==b);
	}

	template<int i>
	std::ostream& operator<<(std::ostream& out, indexed_element_t<i> const& a){
		return out<<"e"<<i;
	}
}

#endif /* GROUP_COMMUTATION_H */
