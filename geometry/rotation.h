#ifndef GEOMETRY_ROTATION_H
#define GEOMETRY_ROTATION_H 

#include"slice.h"
#include"algebra/exponential.h"
#include"../multiplication/reverse.h"

#include<type_traits>

namespace math::geometry{
	//rotation in a single plane
	template<class Direction1, class Direction2, class AngleT=double>
	struct simple_rotation_t{
		plane_t<Direction1,Direction2> plane;
		AngleT angle;

		auto constexpr bivector() const{
			return angle*plane.blade();
		}
		auto constexpr rotor() const{
			return exp(ratio<1,2>*bivector());
		}
		auto constexpr operator()(auto const& a) const{
			auto R=rotor();
			return project(R*a*reverse(R), grades(a));
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
			return project(rotor_*a*reverse(rotor_), grades(a));
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
