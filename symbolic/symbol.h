#ifndef SYMBOL_H
#define SYMBOL_H 

#include<type_traits>

namespace symbolic{
	template<class Name>
	struct symbol_t{};

	template<class T> struct is_symbol: std::false_type{};
	template<class Name> struct is_symbol<symbol_t<Name>>: std::true_type{};
	template<class T> concept bool Symbol=is_symbol<T>::value;
}

#endif /* SYMBOL_H */
