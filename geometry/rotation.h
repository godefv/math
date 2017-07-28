#ifndef GEOMETRY_ROTATION_H
#define GEOMETRY_ROTATION_H 

#include"slice.h"
#include"../algebra/exponential.h"
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
		constexpr auto operator()(auto const& vector){
			auto q=quaternion();
			return q*vector*reverse(q);
		}
	};

	constexpr auto rotation(plane_t<auto,auto> const& plane, auto const& angle){
		using namespace boost::hana::literals;
		return rotation_t<std::decay_t<decltype(plane.directions[0_c])>
		                 ,std::decay_t<decltype(plane.directions[1_c])>
		                 ,std::decay_t<decltype(angle)>
						 >{plane, angle};
	}
}

#endif /* GEOMETRY_ROTATION_H */
