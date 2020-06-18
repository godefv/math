#ifndef SYMBOLIC_SYMBOL_H
#define SYMBOLIC_SYMBOL_H 

#include"name.h"
#include<type_traits>
#include<concepts>

namespace godefv::math{
	//!A Symbol is any type which represents a specific instance of a mathematical object. 
	//!An abstract type x_t is a Symbol even if it can be assigned a value at runtime if it will represent only one specific value
	//!The int type is not a Symbol because it can represent any integer at runtime.
	//!Some operations on even the most abstract symbols can be processed at compile time, such as x*x=x².

	//Symbol concept, is_symbol<> can be specialized to make a type a Symbol
	template<class T> struct is_symbol: std::false_type{};
	template<class T> concept Symbol=is_symbol<T>::value;

	//name_t is a Symbol
	template<char... Name> struct is_symbol<name_t<Name...>>: std::true_type{};

	//!Template to make Symbol types.
	template<class Name>
	struct symbol_t{
		Name name;
	};
	template<Symbol Name> struct is_symbol<symbol_t<Name>>: std::true_type{};

	//operators
	template<class NameT>
	bool operator==(symbol_t<NameT>,symbol_t<NameT>){return true;}
	bool operator==(symbol_t<auto>  ,symbol_t<auto>  ){return false;}
	bool operator!=(symbol_t<auto> a,symbol_t<auto> b){return !(a==b);}

	template<char... letters>
	auto constexpr symbol=symbol_t<name_t<letters...>>{};

	inline namespace literals{
		template<class CharT, CharT... letters>
		auto constexpr operator""_symbol(){return symbol<letters...>;}
	}

	std::ostream& operator<<(std::ostream& out,symbol_t<auto> const& symbol){
		return out<<symbol.name;
	}

	//eval
	template<class NameT, class EvaluatorT> requires std::invocable<EvaluatorT, symbol_t<NameT>>
	auto constexpr eval_with_data(symbol_t<NameT> symbol, EvaluatorT const& evaluator){return evaluator(symbol);}
}

#endif /* SYMBOLIC_SYMBOL_H */
