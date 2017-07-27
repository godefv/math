#ifndef FORMATTING_H
#define FORMATTING_H 

#include"basis.h"
#include"direction.h"
#include"addition.h"
#include"../group/operation.h"

#include<iostream>

namespace vector{
	template<int i>
	std::ostream& operator<<(std::ostream& out, direction_t<i> const& a){
		return out<<"d"<<i;
	}
	template<class ElementT>
	std::ostream& operator<<(std::ostream& out, basis_element_t<ElementT, Scalar> const& a){
		return out<<a.coordinate<<" * "<<ElementT{};
	}
	std::ostream& operator<<(std::ostream& out, group::generated_element_t<add_operation_t<Scalar>, auto, auto> const& ab){
		return out<<"("<<ab.first<<") + ("<<ab.second<<")";
	}
}

#endif /* FORMATTING_H */
