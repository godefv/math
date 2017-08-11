#ifndef GEOMETRY_ROTATION_H
#define GEOMETRY_ROTATION_H 

#include"slice.h"
#include"../algebra/exponential.h"
#include"../algebra/geometric.h"
#include"../algebra/reverse.h"

namespace geometry{
	template<class Direction1, class Direction2, class AngleT=double>
	struct simple_rotation_t{
		plane_t<Direction1,Direction2> plane;
		AngleT angle;

		constexpr auto bivector() const{
			return angle*plane.blade();
		}
		constexpr auto quaternion() const{
			return algebra::exp(0.5*bivector());
		}
		constexpr auto operator()(auto const& a) const{
			auto q=quaternion();
			return algebra::geometric::project(q*a*reverse(q), algebra::geometric::grades(a));
		}
	};

	template<class Direction1, class Direction2, class AngleT>
	simple_rotation_t(plane_t<Direction1,Direction2> const& plane, AngleT const& angle)->simple_rotation_t<Direction1,Direction2,AngleT>;
}

#endif /* GEOMETRY_ROTATION_H */
