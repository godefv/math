#ifndef GEOMETRY_ALGEBRA_DEFINITION_H
#define GEOMETRY_ALGEBRA_DEFINITION_H 

#include"../../multiplication/operation.h"
#include"../../multiplication/power.h"
#include"../../scalar.h"

#include<type_traits>

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

	//Blade concept
	template<class> struct is_blade: std::false_type{};
	template<Direction DirectionT> struct is_blade<DirectionT>: std::true_type{};
	template<Scalar    ScalarT   > struct is_blade<ScalarT   >: std::true_type{};
	
	template<class T> concept bool Blade=is_blade<T>::value;
	
	template<Blade Blade1, Blade Blade2> 
	struct is_blade<group::generated_by_operation_t<mult_operation_t,Blade1,Blade2>>: std::true_type{};
	template<Blade BladeT, class ExponentT> 
	struct is_blade<group::generated_power_t<add_operation_t,ExponentT,BladeT>>: std::true_type{};

	//MultiVector concept
	template<class> struct is_multivector: std::false_type{};
	template<Blade BladeT> struct is_multivector<BladeT>: std::true_type{};
	
	template<class T> concept bool MultiVector=is_multivector<T>::value;
	
	template<MultiVector MultiVectorT, Blade BladeT> 
	struct is_multivector<group::generated_by_operation_t<add_operation_t,MultiVectorT,BladeT>>: std::true_type{};
	template<MultiVector MultiVectorT, class ExponentT> 
	struct is_multivector<group::generated_power_t<add_operation_t,ExponentT,MultiVectorT>>: std::true_type{};
}

namespace math{
	//a direction is a symbol
	template<geometry::Direction DirectionT> struct is_symbol<DirectionT>: std::true_type{};
}

namespace math::geometry{
	//ordering for commutation
	constexpr int static_compare(auto, direction_positive_t<auto> const&, direction_negative_t<auto> const&){return -1;}
	constexpr int static_compare(auto, direction_negative_t<auto> const&, direction_positive_t<auto> const&){return 1;}

	//anticommutation rule : directions are assumed to be orthogonal
	template<Direction A, Direction B> requires static_compare(mult_operation_t{}, A{},B{})<0
	auto constexpr operator*(A const& a, B const& b){
		return -(b*a);
	}

	//cyclic order
	auto constexpr cycle_order(mult_operation_t, direction_positive_t<auto>){
		return 2;
	}
	auto constexpr cycle_order(mult_operation_t, direction_negative_t<auto>){
		return 4;
	}

	auto constexpr generated_power(mult_operation_t, integer_t<2>, direction_negative_t<auto> const&){
		return -one;
	}
	auto constexpr generated_power(mult_operation_t, integer_t<3>, direction_negative_t<auto> const& ei){
		return -ei;
	}
}

#endif /* GEOMETRY_ALGEBRA_DEFINITION_H */
