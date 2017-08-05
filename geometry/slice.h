#ifndef GEOMETRY_SLICE_H
#define GEOMETRY_SLICE_H 

#include"../algebra/geometric.h"

#include<boost/hana.hpp>

namespace geometry{
	template<class... DirectionTypes>
	struct slice_t{
		boost::hana::tuple<DirectionTypes...> directions;

		constexpr slice_t()=default;
		constexpr slice_t(DirectionTypes const&... directions_):directions{boost::hana::make_tuple(directions_...)}{}

		auto constexpr blade() const{
			return boost::hana::fold(directions, [](auto const& a, auto const& b){return a^b;});
		}
	};

	template<class Direction1, class Direction2>
	using plane_t=slice_t<Direction1, Direction2>;

	constexpr auto plane(auto const& a, auto const& b){return slice_t(a,b);}
}

#endif /* GEOMETRY_SLICE_H */
