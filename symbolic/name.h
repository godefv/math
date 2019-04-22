#ifndef NAME_H
#define NAME_H 

#include<iostream>

namespace godefv::math{
	//!Template to make symbol names from letters
	template<char...> struct name_t{};

	template<char... Name>
	bool constexpr operator==(name_t<Name...> const&, name_t<Name...> const&){
		return true;
	}
	template<char... Name1, char... Name2>
	bool constexpr operator==(name_t<Name1...> const&, name_t<Name2...> const&){
		return false;
	}
	template<char... Name1, char... Name2>
	bool constexpr operator!=(name_t<Name1...> const& a, name_t<Name2...> const& b){
		return !(a==b);
	}

	//formatting
	template<char... Name> 
	std::ostream& operator<<(std::ostream& out,name_t<Name...>){
		return (out<<...<<Name);
	}
}

#endif /* NAME_H */
