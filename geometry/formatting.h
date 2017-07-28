#ifndef GEOMETRY_FORMATTING_H
#define GEOMETRY_FORMATTING_H 

#include"direction.h"

#include<iostream>

namespace geometry{
	template<int i>
	std::ostream& operator<<(std::ostream& out, direction_t<i> const& a){
		return out<<"d"<<i;
	}
}

#endif /* GEOMETRY_FORMATTING_H */
