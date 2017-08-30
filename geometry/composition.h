#ifndef GEOMETRY_COMPOSITION_H
#define GEOMETRY_COMPOSITION_H 

#include"rotation.h"
#include"../group/operation.h"

#include<iostream>

namespace geometry{
	struct compose_operation_t{
		static auto constexpr apply(simple_rotation_t<auto,auto,auto> const& a, simple_rotation_t<auto,auto,auto> const& b){
			using namespace algebra::geometric;
			using namespace algebra::geometric::operators;
			using namespace hana::literals;

			auto ab_rotor=a.rotor()*b.rotor();

			if constexpr(hana::find(grades(ab_rotor), 4_c)==hana::nothing){
				auto ab_angle=2*std::acos(project(ab_rotor, grades<0>()).coordinate);
				auto ab_blade=project(ab_rotor, grades<2>());
				auto d1=ab_blade|a.plane.directions[1_c];
				auto d2=d1|ab_blade/(d1|d1);
				return simple_rotation_t{plane(d1,d2), ab_angle};
			}
			else{
				return group::operation<compose_operation_t>(a,b);
			}
		}

		static auto constexpr inverse(simple_rotation_t<auto,auto,auto> const& a){
			return simple_rotation_t{a.plane, -a.angle};
		}
	};

	std::ostream& operator<<(std::ostream& out, group::generated_element_t<auto,auto,auto> const& ab){
		return out<<ab.first<<" o "<<ab.second;
	}
}

#endif /* GEOMETRY_COMPOSITION_H */
