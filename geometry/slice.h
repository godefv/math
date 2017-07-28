#ifndef GEOMETRY_SLICE_H
#define GEOMETRY_SLICE_H 

#include<boost/hana.hpp>

namespace geometry{
	template<class... DirectionTypes>
	struct slice_t{
		boost::hana::tuple<DirectionTypes...> directions;

		slice_t()=default;
		slice_t(DirectionTypes const&... directions_):directions{boost::hana::make_tuple(directions_...)}{}
	};

	template<class Direction1, class Direction2>
	using plane_t=slice_t<Direction1, Direction2>;
}

#endif /* GEOMETRY_SLICE_H */
