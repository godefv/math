#ifndef GEOMETRY_COMPOSITION_H
#define GEOMETRY_COMPOSITION_H 

#include"rotation.h"
#include"../group/operation.h"

namespace geometry{
	struct compose_operation_t{
		static auto constexpr apply(simple_rotation_t<auto,auto,auto> const& a, simple_rotation_t<auto,auto,auto> const& b){
			if constexpr(a.plane.blade()==b.plane.blade()){
				return std::decay_t<decltype(a)>{a.plane, a.angle+b.angle};
			}
			else if constexpr(a.plane.blade()|b.plane.blade()==algebra::geometric::zero){
				return group::operation<compose_operation_t>(a,b);
			}
			else{
				auto ab_quaternion=a.quaternion()*b.quaternion();
				auto ab_angle=std::acos(project(ab_quaternion, algebra::geometric::grades<0>()));
				auto ab_blade=normalized(project(ab_quaternion, algebra::geometric::grades<2>()));
				return simple_rotation_t{ab_blade, ab_angle};
			}
		}

		static auto constexpr inverse(simple_rotation_t<auto,auto,auto> const& a){
			return std::decay_t<decltype(a)>{a.plane, -a.angle};
		}
	};
}

#endif /* GEOMETRY_COMPOSITION_H */
