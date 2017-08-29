#ifndef GEOMETRY_COMPOSITION_H
#define GEOMETRY_COMPOSITION_H 

#include"rotation.h"
#include"../group/operation.h"

namespace geometry{
	struct compose_operation_t{
		static auto constexpr apply(simple_rotation_t<auto,auto,auto> const& a, simple_rotation_t<auto,auto,auto> const& b){
			using namespace algebra::geometric;
			using namespace algebra::geometric::operators;

			auto ab_rotor=a.rotor()*b.rotor();

			if constexpr(hana::find(grades(ab_rotor), 4_c)==hana::nothing){
				//auto ab_angle=std::acos(project(ab_rotor, grades<0>()).coordinate);
				//auto ab_blade=project(ab_rotor, grades<2>());
				//return simple_rotation_t{ab_blade, ab_angle};
				return ab_rotor;
			}
			else{
				return group::operation<compose_operation_t>(a,b);
			}
		}

		static auto constexpr inverse(simple_rotation_t<auto,auto,auto> const& a){
			return std::decay_t<decltype(a)>{a.plane, -a.angle};
		}
	};
}

#endif /* GEOMETRY_COMPOSITION_H */
