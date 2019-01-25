#ifndef GEOMETRY_TRANSFORM_H
#define GEOMETRY_TRANSFORM_H 

#include"rotation.h"
#include"scaling.h"
#include"translation.h"
#include"composition.h"

namespace math::geometry{
	template<class F> concept bool VectorTransform=requires(F f){
		requires KVector<decltype(
			f(2.5*direction_negative_t<name_t<'x'>>{}+ratio<3,5>*direction_positive_t<name_t<'t'>>{})
		), 1>;
	};

	auto constexpr apply(VectorTransform const& transform, translation_t<auto> const& operand){
		return translation_t{apply(transform, operand.vector)};
	}

	//composition of vector transformations - scalings
	Scaling{Scaling2}
	auto constexpr operator,(Scaling const& a, Scaling2 const& b){
		return scaling_t{a.factor*b.factor};
	}
	//composition of vector transformations - rotations
	VectorRotation{VectorRotation2}
	auto constexpr operator,(VectorRotation const& a, VectorRotation2 const& b){
		auto ab_rotor=b.rotor()*a.rotor();
		//auto bivector_part=project(ab_rotor, grades<2>());
		//if constexpr(grades(ab_rotor)==grades<0,2>() && group::geometric::Blade<decltype(bivector_part)>){
			//return simple_rotation_t{};
		//}else{
		if constexpr(grades(ab_rotor)==grades<0>()){
			return identity;
		}else{
			return rotation_t{ab_rotor};
		}
		//}
	}
	//composition of vector transformations - put scalings first
   	auto constexpr operator,(VectorRotation const& a, Scaling const& b){
   		return b,a;
   	}

}

#endif /* GEOMETRY_TRANSFORM_H */
