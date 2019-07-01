#ifndef GEOMETRY_OBJECT_DIRECTION_H
#define GEOMETRY_OBJECT_DIRECTION_H 

#include"../../symbolic/symbol.h"
#include"../../scalar.h"

#include<boost/hana.hpp>
#include<type_traits>
#include<iostream>

namespace godefv::math::geometry{
	//directions definition
	struct direction_tag_t{};
	template<class Name> struct direction_positive_t{Name name;using hana_tag=direction_tag_t;};
	template<class Name> struct direction_negative_t{Name name;using hana_tag=direction_tag_t;};

	//direction concept
	template<class> struct is_direction_t: std::false_type{};
	template<class Name> struct is_direction_t<direction_positive_t<Name>>: std::true_type{};
	template<class Name> struct is_direction_t<direction_negative_t<Name>>: std::true_type{};
	template<class A> concept bool Direction=is_direction_t<A>::value && Symbol<A> && !Scalar<A> && !SimpleScalar<A>; // last term is needed because gcc does not expand !(x||y) to (!x && !y)

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
	inline namespace literals{
		template<class CharT, CharT... letters>
		auto constexpr operator""_direction_positive(){return direction_positive<letters...>;}
		template<class CharT, CharT... letters>
		auto constexpr operator""_direction_negative(){return direction_negative<letters...>;}
	}
}

namespace godefv::math{
	//a direction is a symbol
	template<Symbol Name> struct is_symbol<geometry::direction_positive_t<Name>>: std::true_type{};
	template<Symbol Name> struct is_symbol<geometry::direction_negative_t<Name>>: std::true_type{};

}

namespace boost::hana {
    // Comparable

    template <>
    struct equal_impl<godefv::math::geometry::direction_tag_t, godefv::math::geometry::direction_tag_t> {
		godefv::math::geometry::Direction{Direction2}
        static constexpr auto apply(godefv::math::geometry::Direction const& a, Direction2 const& b)
            -> hana::bool_<std::is_same_v<decltype(a), decltype(b)>>
        { return {}; }

        template <typename T, typename U>
        static constexpr auto apply(T, T)
            -> hana::true_
        { return {}; }
    };

    // Hashable

    template <>
    struct hash_impl<godefv::math::geometry::direction_tag_t> {
        template <typename T>
        static constexpr auto apply(T)
            -> hana::type<T>
        { return {}; }
    };
}

#endif /* GEOMETRY_OBJECT_DIRECTION_H */
