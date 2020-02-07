#ifndef GEOMETRY_SLICE_H
#define GEOMETRY_SLICE_H 

#include"../algebra/wedge_product.h"
#include"../algebra/norm.h"

#include"../../hana.h"

#include<iostream>

namespace godefv::math::geometry{
	namespace hana=boost::hana;

	template<Vector... DirectionTypes>
	struct slice_t{
		hana::tuple<DirectionTypes...> directions;

		constexpr slice_t()=default;
		constexpr slice_t(DirectionTypes const&... directions_):directions{hana::make_tuple(directions_...)}{}

		auto constexpr blade() const{
			return normalized(directions|hana::fold_with(wedge_operation_t{}));
		}
	};

	template<Vector Direction1, Vector Direction2>
	using plane_t=slice_t<Direction1, Direction2>;

	constexpr auto plane(auto const& a, auto const& b){return slice_t(a,b);}

	template<Vector... DirectionTypes>
	std::ostream& operator<<(std::ostream& out, slice_t<DirectionTypes...> const& slice){
		using namespace hana::literals;
		return hana::fold(hana::drop_front(slice.directions), out<<"slice{"<<slice.directions[0_c], [](std::ostream& o, auto const& d)->std::ostream&{return o<<", "<<d;})<<"}";
	}
}

#endif /* GEOMETRY_SLICE_H */
