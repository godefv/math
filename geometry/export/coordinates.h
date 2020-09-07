#ifndef GEOMETRY_EXPORT_COORDINATES_H
#define GEOMETRY_EXPORT_COORDINATES_H 

#include<iostream>
#include<vector>

namespace godefv::math::geometry{
	namespace hana=boost::hana;

	template<class... DirectionsT>
	auto compute_coordinates(hana::tuple<DirectionsT...> const& reciprocal_frame, auto const& point){
		return reciprocal_frame
			|hana::transform_with([&point](auto const& direction){return (point|direction);});
	}

	template<class... DirectionsT>
	std::ostream& print_coordinates(std::ostream& out, std::vector<auto> const& vectors, hana::tuple<DirectionsT...> const reference_frame){
		auto constexpr reciprocal_frame=reference_frame|hana::transform_with([&](auto const& direction){return inverse(direction);});
		for(auto const& point:vectors){
			hana::fold(compute_coordinates(reciprocal_frame, point), out, [](std::ostream& o, auto const& coord)->std::ostream&{return o<<coord<<" ";});
		}
		return out;
	}
}

#endif /* GEOMETRY_EXPORT_COORDINATES_H */
