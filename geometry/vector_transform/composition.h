#ifndef GEOMETRY_TRANSFORM_H
#define GEOMETRY_TRANSFORM_H 

#include"rotation.h"
#include"scaling.h"
#include"../../composition/operation.h"

namespace godefv::math::geometry{
	template<class F> concept VectorTransform=requires(F f){
		requires KVector<decltype(
			f(2.5*direction_negative_t<name_t<'x'>>{}+ratio<3,5>*direction_positive_t<name_t<'t'>>{})
		), 1>;
	};

	//composition of vector transformations - scalings
	auto constexpr operator,(Scaling auto const& a, Scaling auto const& b){
		return scaling_t{a.factor*b.factor};
	}
	//composition of vector transformations - rotations
	auto constexpr operator,(VectorRotation auto const& a, VectorRotation auto const& b){
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
   	auto constexpr operator,(VectorRotation auto const& a, Scaling auto const& b){
   		return b,a;
   	}

}

#endif /* GEOMETRY_TRANSFORM_H */
