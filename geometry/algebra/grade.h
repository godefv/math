#ifndef GEOMETRY_ALGEBRA_GRADE_H
#define GEOMETRY_ALGEBRA_GRADE_H 

#include"definition.h"
#include"../../group/morphism.h"

#include<boost/hana.hpp>

namespace math::geometry{
	//grade of blades
	auto constexpr grade(Scalar const&){return 0;}
	auto constexpr grade(Direction const&){return 1;}
	//grade is a morphism from * to +
	Blade{Blade2}
	auto constexpr grade(group::generated_by_operation_t<mult_operation_t, Blade,Blade2> const& a){
		return grade(a.first)+grade(a.second);
	}
	auto constexpr grade(group::generated_power_t<add_operation_t, Scalar, Blade> const& a){
		return grade(a.operand);
	}

	namespace hana=boost::hana;

	//!Convenience function to make a set of grades.
	template<int... Is>
	auto constexpr grades(){return hana::make_set(hana::llong_c<Is>...);}
	
	//grades is a morphism from (auto,+) to (hana::set,hana::union)
	auto constexpr grades_functor=group::morphism_t{add_operation_t{}, hana::union_, [](Blade const& operand){return grades<grade(operand)>();}};
	auto constexpr grades(MultiVector const& operand){return grades_functor(operand);}

	//KVector concept
	template<MultiVector T, int K> concept bool KVector=hana::value(grades(T{})==grades<K>());
	template<class T> concept bool Vector=KVector<T,1>;
	template<class T> concept bool BiVector=KVector<T,2>;
	//KBlade concept
	template<class T, int K> concept bool KBlade=KVector<T,K> && Scalar<std::decay_t<decltype(square(T{}))>>;


	//project multivector onto a set of grades
	auto constexpr project=group::endomorphism(add_operation_t{}, [](Blade const& blade, auto grades){
		if constexpr(hana::find(grades, hana::llong_c<grade(blade)>)==hana::nothing){
			return zero;
		}else{
			return blade;
		}
	});
}

#endif /* GEOMETRY_ALGEBRA_GRADE_H */
