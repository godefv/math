#ifndef SYMBOLIC_SYMBOL_H
#define SYMBOLIC_SYMBOL_H 

#include<iostream>
#include<type_traits>

namespace math{
	//!A Symbol is any type which represents a specific instance of a mathematical object. 
	//!An abstract type x_t is a Symbol even if it can be assigned a value at runtime if it will represent only one specific value at a given time. 
	//!The int type is not a Symbol because it can represent any integer at runtime.
	//!Some operations on even the most abstract symbols can be processed at compile time, such as x*x=x².

	//!Template to make Symbol types.
	template<class Name>
	struct symbol_t{};

	//operators
	template<class NameT>
	bool operator==(symbol_t<NameT>,symbol_t<NameT>){return true;}
	bool operator==(symbol_t<auto> a,symbol_t<auto> b){return false;}
	bool operator!=(symbol_t<auto> a,symbol_t<auto> b){return !(a==b);}

	//Symbol concept, is_symbol<> can be specialized to make a type a Symbol
	template<class T> struct is_symbol: std::false_type{};
	template<class Name> struct is_symbol<symbol_t<Name>>: std::true_type{};
	template<class T> concept bool Symbol=is_symbol<T>::value;

	//!Template to make symbol names from letters
	template<char...> struct symbol_name_t{};

	template<char... letters>
	auto constexpr symbol=symbol_t<symbol_name_t<letters...>>{};

	template<class CharT, CharT... letters>
	auto constexpr operator""_symbol(){return symbol<letters...>;}

	//formatting
	template<char... Name> std::ostream& operator<<(std::ostream& out,symbol_t<symbol_name_t<Name...>>){return (out<<...<<Name);}
}

#endif /* SYMBOLIC_SYMBOL_H */
