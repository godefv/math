#ifndef GEOMETRY_OBJECT_DIRECTION_H
#define GEOMETRY_OBJECT_DIRECTION_H 

#include"../../symbolic/symbol.h"

#include<type_traits>
#include<iostream>

namespace math::geometry{
	//directions definition
	template<class Name> struct direction_positive_t{Name name;};
	template<class Name> struct direction_negative_t{Name name;};

	//direction concept
	template<class> struct is_direction_t: std::false_type{};
	template<class Name> struct is_direction_t<direction_positive_t<Name>>: std::true_type{};
	template<class Name> struct is_direction_t<direction_negative_t<Name>>: std::true_type{};
	template<class A> concept bool Direction=is_direction_t<A>::value;

	//operators
	bool constexpr operator==(direction_positive_t<auto> const& a, direction_positive_t<auto> const& b){
		return a.name==b.name;
	}
	bool constexpr operator==(direction_negative_t<auto> const& a, direction_negative_t<auto> const& b){
		return a.name==b.name;
	}
	//bool constexpr operator==(Direction const& a, Direction const& b){
		//return false;
	//}
	bool constexpr operator!=(Direction const& a, Direction const& b){
		return !(a==b);
	}
	std::ostream& operator<<(std::ostream& out, Direction const& operand){
		return out<<operand.name;
	}
	template<char... letters>
	auto constexpr direction_positive=direction_positive_t<name_t<letters...>>{};
	template<char... letters>
	auto constexpr direction_negative=direction_negative_t<name_t<letters...>>{};
	namespace literals{
		template<class CharT, CharT... letters>
		auto constexpr operator""_direction_positive(){return direction_positive<letters...>;}
		template<class CharT, CharT... letters>
		auto constexpr operator""_direction_negative(){return direction_negative<letters...>;}
	}
}

namespace math{
	//a direction is a symbol
	template<geometry::Direction DirectionT> struct is_symbol<DirectionT>: std::true_type{};
}

#endif /* GEOMETRY_OBJECT_DIRECTION_H */
