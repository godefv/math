#ifndef NAME_H
#define NAME_H 

#include<iostream>

namespace math{
	//!Template to make symbol names from letters
	template<char...> struct name_t{};

	//formatting
	template<char... Name> 
	std::ostream& operator<<(std::ostream& out,name_t<Name...>){
		return (out<<...<<Name);
	}
}

#endif /* NAME_H */
