#ifndef SYMBOLIC_SYMBOL_H
#define SYMBOLIC_SYMBOL_H 

#include<iostream>
#include<type_traits>

namespace math{
	template<class Name>
	struct symbol_t{};

	template<class T> struct is_symbol: std::false_type{};
	template<class Name> struct is_symbol<symbol_t<Name>>: std::true_type{};
	template<class T> concept bool Symbol=is_symbol<T>::value;

	inline bool operator==(symbol_t<auto>,symbol_t<auto>){return true;}
	inline bool operator!=(symbol_t<auto>,symbol_t<auto>){return false;}

	template<char> struct symbol_name_t{};

	template<char Name> std::ostream& operator<<(std::ostream& out,symbol_t<symbol_name_t<Name>>){return out<<Name;}
}

#endif /* SYMBOLIC_SYMBOL_H */
