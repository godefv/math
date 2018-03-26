#ifndef GEOMETRY_ALGEBRA_DEFINITION_H
#define GEOMETRY_ALGEBRA_DEFINITION_H 

#include"../../multiplication/operation.h"
#include"../../multiplication/power.h"
#include<type_traits>

namespace math::geometry{
	//directions definition
	template<unsigned short i> struct direction_positive_t:indexed_element_t<i>{};
	template<unsigned short i> struct direction_negative_t:indexed_element_t<-i>{};

	//direction concept
	template<class> struct is_direction_t: std::false_type{};
	template<unsigned short i> struct is_direction_t<direction_positive_t<i>>: std::true_type{};
	template<unsigned short i> struct is_direction_t<direction_negative_t<i>>: std::true_type{};
	template<class A> concept bool Direction=is_direction_t<A>::value;

	//blade concept
	template<class> struct is_blade_t: std::false_type{};
	template<Direction DirectionT> struct is_blade_t<DirectionT>: std::true_type{};
	
	template<class T> concept bool Blade=is_blade_t<T>::value;
	
	template<Blade BladeT, Direction DirectionT> 
	struct is_blade_t<group::generated_by_operation_t<mult_operation_t,BladeT,DirectionT>>: std::true_type{};
}

namespace math{
	//a blade is a symbol
	template<geometry::Blade BladeT> struct is_symbol<BladeT>: std::true_type{};
}

namespace math::geometry{
	//ordering for commutation
	Direction{Direction2}
	constexpr int static_compare(Direction const& a, Direction2 const& b){return b.index-a.index;}

	//anticommutation rule : directions are assumed to be orthogonal
	template<Direction A, Direction B> requires static_compare(A{},B{})<0
	auto constexpr operator*(A const& a, B const& b){
		return -(b*a);
	}

	//cyclic order
	template<unsigned short i>
	auto constexpr cycle_order(mult_operation_t, direction_positive_t<i>){
		return 2;
	}
	template<unsigned short i>
	auto constexpr cycle_order(mult_operation_t, direction_negative_t<i>){
		return 4;
	}

	template<unsigned short i>
	auto constexpr generated_power(mult_operation_t, integer_t<2>, direction_negative_t<i> const&){
		return -one;
	}
	template<unsigned short i>
	auto constexpr generated_power(mult_operation_t, integer_t<3>, direction_negative_t<i> const& ei){
		return -ei;
	}
}

#endif /* GEOMETRY_ALGEBRA_DEFINITION_H */
