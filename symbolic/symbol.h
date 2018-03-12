#ifndef SYMBOLIC_SYMBOL_H
#define SYMBOLIC_SYMBOL_H 

#include<type_traits>

namespace symbolic{
	template<class Name>
	struct symbol_t{};

	template<class T> struct is_symbol: std::false_type{};
	template<class Name> struct is_symbol<symbol_t<Name>>: std::true_type{};
	template<class T> concept bool Symbol=is_symbol<T>::value;

	inline bool operator==(symbolic::symbol_t<auto>,symbolic::symbol_t<auto>){return true;}
	inline bool operator!=(symbolic::symbol_t<auto>,symbolic::symbol_t<auto>){return false;}
}

#endif /* SYMBOLIC_SYMBOL_H */
