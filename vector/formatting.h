#ifndef FORMATTING_H
#define FORMATTING_H 

#include"basis.h"
#include"addition.h"
#include"../group/operation.h"

#include<iostream>

namespace vector{
	template<class ElementT>
	std::ostream& operator<<(std::ostream& out, basis_element_t<ElementT, Scalar> const& a){
		return out<<a.coordinate<<" * "<<ElementT{};
	}
	std::ostream& operator<<(std::ostream& out, group::generated_element_t<add_operation_t<Scalar>, auto, auto> const& ab){
		return out<<"("<<ab.first<<") + ("<<ab.second<<")";
	}
}

#endif /* FORMATTING_H */
