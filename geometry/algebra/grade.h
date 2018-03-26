#ifndef GEOMETRY_ALGEBRA_GRADE_H
#define GEOMETRY_ALGEBRA_GRADE_H 

#include"definition.h"

#include<boost/hana.hpp>

namespace math::geometry{
	//grade of blades
	auto constexpr grade(Scalar const&){return 0;}
	auto constexpr grade(Direction const&){return 1;}
	Blade{Blade2}
	auto constexpr grade(group::generated_by_operation_t<mult_operation_t, Blade,Blade2> const& a){
		return grade(a.first)+grade(a.second);
	}
	auto constexpr grade(group::generated_power_t<add_operation_t, Ratio, Blade> const& a){
		return grade(a.operand);
	}

	namespace hana=boost::hana;

	template<int... Is>
	auto constexpr grades(){return hana::make_set(hana::llong_c<Is>...);}
	auto constexpr grades(zero_t const&){return grades<>();}
	auto constexpr grades(Blade const& a){return grades<grade(a)>();}
	MultiVector{MultiVector2}
	auto constexpr grades(group::generated_by_operation_t<add_operation_t, MultiVector,MultiVector2> const& a){
		return hana::union_(grades(a.first), grades(a.second));
	}

	auto constexpr project(zero_t, auto){return zero;}
	auto constexpr project(Blade const& blade, auto grades){
		if constexpr(hana::find(grades, hana::llong_c<grade(blade)>)==hana::nothing){
			return zero;
		}else{
			return blade;
		}
	}
	MultiVector{MultiVector2}
	auto constexpr project(group::generated_by_operation_t<add_operation_t, MultiVector,MultiVector2> const& a, auto grades){
		return project(a.first, grades)+project(a.second, grades);
	}
}

#endif /* GEOMETRY_ALGEBRA_GRADE_H */
