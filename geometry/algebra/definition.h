#ifndef GEOMETRY_ALGEBRA_DEFINITION_H
#define GEOMETRY_ALGEBRA_DEFINITION_H 

#include"../object/direction.h"
#include"../../multiplication/all.h"
#include"../../scalar.h"

#include<type_traits>

namespace godefv::math::geometry{
	//Blade concept, actually a restricted version where e1e2+e2e3 is not considered a blade because we don't factor it as (e1-e3)e2
	template<class> struct is_blade: std::false_type{};
	template<Direction DirectionT> struct is_blade<DirectionT>: std::true_type{};
	template<Scalar    ScalarT   > struct is_blade<ScalarT   >: std::true_type{};
	
	template<class T> concept Blade=is_blade<T>::value;
	template<class T> concept NonZeroBlade=Blade<T> && !Zero<T>;
	
	template<Blade Blade1, Blade Blade2> 
	struct is_blade<group::generated_by_operation_t<mult_operation_t,Blade1,Blade2>>: std::true_type{};
	template<Blade BladeT, class ExponentT> 
	struct is_blade<group::generated_power_t<add_operation_t,ExponentT,BladeT>>: std::true_type{};

	//MultiVector concept
	template<class> struct is_multivector: std::false_type{};
	template<Blade BladeT> struct is_multivector<BladeT>: std::true_type{};
	
	template<class T> concept MultiVector=is_multivector<T>::value;
	
	template<MultiVector MultiVectorT, Blade BladeT> 
	struct is_multivector<group::generated_by_operation_t<add_operation_t,MultiVectorT,BladeT>>: std::true_type{};
	template<MultiVector MultiVectorT, class ExponentT> 
	struct is_multivector<group::generated_power_t<add_operation_t,ExponentT,MultiVectorT>>: std::true_type{};

	//ordering for commutation
	constexpr int static_compare(auto, direction_positive_t<auto> const&, direction_negative_t<auto> const&){return -1;}
	constexpr int static_compare(auto, direction_negative_t<auto> const&, direction_positive_t<auto> const&){return 1;}

	//anticommutation rule : directions are assumed to be orthogonal
	template<Direction A, Direction B> requires static_compare(mult_operation_t{}, A{},B{})<0
	auto constexpr operator*(A const& a, B const& b){
		return -(b*a);
	}
}

#endif /* GEOMETRY_ALGEBRA_DEFINITION_H */
