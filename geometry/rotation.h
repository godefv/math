#ifndef GEOMETRY_ROTATION_H
#define GEOMETRY_ROTATION_H 

#include"slice.h"
#include"../symbolic/trigonometry.h"
#include"../algebra/exponential.h"
#include"../algebra/geometric.h"
#include"../algebra/reverse.h"

namespace geometry{
	template<class Direction1, class Direction2, class AngleT=double>
	struct simple_rotation_t{
		plane_t<Direction1,Direction2> plane;
		AngleT angle;

		constexpr auto bivector() const{
			using namespace algebra::geometric::operators;
			return angle*plane.blade();
		}
		constexpr auto rotor() const{
			using namespace algebra::geometric::operators;
			return algebra::exp<group::geometric::one_t>(symbolic::ratio<1,2>*bivector());
		}
		constexpr auto operator()(auto const& a) const{
			using namespace algebra::geometric::operators;
			auto R=rotor();
			return algebra::geometric::project(R*a*reverse(R), algebra::geometric::grades(a));
		}
	};

	template<class Direction1, class Direction2, class AngleT>
	simple_rotation_t(plane_t<Direction1,Direction2> const& plane, AngleT const& angle)->simple_rotation_t<Direction1,Direction2,AngleT>;

	std::ostream& operator<<(std::ostream& out, simple_rotation_t<auto,auto,auto> const& r){
		return out<<"rotation{"<<r.plane<<" ; "<<r.angle<<"}";
	}
}

#endif /* GEOMETRY_ROTATION_H */
