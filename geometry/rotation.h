#ifndef GEOMETRY_ROTATION_H
#define GEOMETRY_ROTATION_H 

#include"slice.h"
#include"../algebra/exponential.h"
#include"../algebra/geometric.h"
#include"../algebra/reverse.h"

#include<boost/hana.hpp>

namespace geometry{
	template<class Direction1, class Direction2, class AngleT=double>
	struct rotation_t{
		plane_t<Direction1,Direction2> plane;
		AngleT angle;

		constexpr auto quaternion(){
			using namespace boost::hana::literals;
			return algebra::exp((angle/2)*plane.directions[1_c]*plane.directions[0_c]);
		}
		constexpr auto operator()(auto const& a){
			auto q=quaternion();
			return algebra::geometric::project(q*a*reverse(q), algebra::geometric::grades(a));
		}
	};

	template<class Direction1, class Direction2, class AngleT>
	rotation_t(plane_t<Direction1,Direction2> const& plane, AngleT const& angle)->rotation_t<Direction1,Direction2,AngleT>;
}

#endif /* GEOMETRY_ROTATION_H */
