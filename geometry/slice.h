#ifndef GEOMETRY_SLICE_H
#define GEOMETRY_SLICE_H 

#include"algebra/wedge_product.h"
#include"algebra/norm.h"

#include<boost/hana.hpp>
#include<iostream>

namespace math::geometry{
	template<KVector<1>... DirectionTypes>
	struct slice_t{
		boost::hana::tuple<DirectionTypes...> directions;

		constexpr slice_t()=default;
		constexpr slice_t(DirectionTypes const&... directions_):directions{boost::hana::make_tuple(directions_...)}{}

		auto constexpr blade() const{
			return normalized(boost::hana::fold(directions, [](auto const& a, auto const& b){
				return a^b;
			}));
		}
	};

	template<KVector<1> Direction1, KVector<1> Direction2>
	using plane_t=slice_t<Direction1, Direction2>;

	constexpr auto plane(auto const& a, auto const& b){return slice_t(a,b);}

	template<KVector<1>... DirectionTypes>
	std::ostream& operator<<(std::ostream& out, slice_t<DirectionTypes...> const& slice){
		using namespace boost::hana::literals;
		return boost::hana::fold(boost::hana::drop_front(slice.directions), out<<"slice{"<<slice.directions[0_c], [](std::ostream& o, auto const& d)->std::ostream&{return o<<", "<<d;})<<"}";
	}
}

#endif /* GEOMETRY_SLICE_H */
