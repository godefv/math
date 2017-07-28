#ifndef GEOMETRY_ROTATION_H
#define GEOMETRY_ROTATION_H 

#include"../algebra/exponential.h"

#include<boost/hana.hpp>

namespace geometry{
	template<class PlaneT, class AngleT=double>
	struct rotation_t{
		PlaneT plane;
		AngleT angle;

		constexpr auto quaternion(){
			using namespace boost::hana::literals;
			return algebra::exp((angle/2)*plane.directions[0_c]*plane.directions[1_c]);
		}
	};
}

#endif /* GEOMETRY_ROTATION_H */
