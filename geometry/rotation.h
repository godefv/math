#ifndef GEOMETRY_ROTATION_H
#define GEOMETRY_ROTATION_H 

#include"slice.h"
#include"../symbolic/trigonometry.h"
#include"../algebra/exponential.h"
#include"../algebra/geometric.h"
#include"../algebra/reverse.h"
#include<type_traits>

namespace geometry{
	//rotation in a single plane
	template<class Direction1, class Direction2, class AngleT=double>
	struct simple_rotation_t{
		plane_t<Direction1,Direction2> plane;
		AngleT angle;

		auto constexpr bivector() const{
			using algebra::geometric::operators::operator*;
			return vector::scalar_wrapper_t{angle}*plane.blade();
		}
		auto constexpr rotor() const{
			using algebra::geometric::operators::operator*;
			return algebra::geometric::exp(symbolic::ratio<1,2>*bivector());
		}
		auto constexpr operator()(auto const& a) const{
			auto R=rotor();
			using algebra::geometric::operators::operator*;
			return algebra::geometric::project(R*a*reverse(R), algebra::geometric::grades(a));
		}
	};

	template<class Direction1, class Direction2, class AngleT>
	simple_rotation_t(plane_t<Direction1,Direction2> const& plane, AngleT const& angle)->simple_rotation_t<Direction1,Direction2,AngleT>;

	std::ostream& operator<<(std::ostream& out, simple_rotation_t<auto,auto,auto> const& r){
		return out<<"rotation{"<<r.plane<<" ; "<<r.angle<<"}";
	}

	//arbitrary rotation
	template<class RotorT>
	struct rotation_t{
		RotorT rotor_;
		auto constexpr rotor() const{return rotor_;}
		auto constexpr operator()(auto const& a) const{
			using namespace algebra::geometric::operators;
			return algebra::geometric::project(rotor*a*reverse(rotor), algebra::geometric::grades(a));
		}
	};

	template<class RotorT>
	rotation_t(RotorT const&)->rotation_t<RotorT>;

	std::ostream& operator<<(std::ostream& out, rotation_t<auto> const& r){
		return out<<"rotation{"<<r.rotor()<<"}";
	}

	//concept
	template<class> struct is_rotation:std::false_type{};
	template<class Direction1, class Direction2, class AngleT>
	struct is_rotation<simple_rotation_t<Direction1,Direction2,AngleT>>:std::true_type{};
	template<class RotorT>
	struct is_rotation<rotation_t<RotorT>>:std::true_type{};
	template<class T> concept bool Rotation=is_rotation<T>::value;

}

#endif /* GEOMETRY_ROTATION_H */
