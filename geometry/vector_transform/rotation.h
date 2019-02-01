#ifndef GEOMETRY_ROTATION_H
#define GEOMETRY_ROTATION_H 

#include"../object/slice.h"
#include"../apply.h"
#include"../algebra/exponential.h"
#include"../../multiplication/reverse.h"

#include<type_traits>

namespace math::geometry{
	//rotation in a single plane
	template<Vector Direction1, Vector Direction2, class AngleT=double>
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
			return apply(*this, a);
		}
	};

	template<Vector Direction1, Vector Direction2, class AngleT>
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
			return apply(*this, a);
		}
	};

	template<class RotorT>
	rotation_t(RotorT const&)->rotation_t<RotorT>;

	std::ostream& operator<<(std::ostream& out, rotation_t<auto> const& r){
		return out<<"rotation{"<<r.rotor()<<"}";
	}

	//concept
	template<class> struct is_rotation:std::false_type{};
	template<Vector Direction1, Vector Direction2, class AngleT>
	struct is_rotation<simple_rotation_t<Direction1,Direction2,AngleT>>:std::true_type{};
	template<class RotorT>
	struct is_rotation<rotation_t<RotorT>>:std::true_type{};
	template<class T> concept bool VectorRotation=is_rotation<T>::value;

	//inverse
	auto constexpr inverse(simple_rotation_t<auto,auto,auto> const& a){
		return simple_rotation_t{a.plane, -a.angle};
	}
	auto constexpr inverse(rotation_t<auto> const& a){
		return rotation_t{reverse(a.rotor())};
	}

	//multivector
	auto constexpr multivector(VectorRotation const& a){
		return a.rotor();
	}

	//apply
	auto constexpr apply(VectorRotation const& rotation, MultiVector const& operand){
		auto R=rotation.rotor();
		return project(R*operand*reverse(R), grades(operand));
	}

	//comparison operators
	VectorRotation{VectorRotation2}
	bool constexpr operator==(VectorRotation const& a, VectorRotation2 const& b){
		return a.rotor()==b.rotor();
	}
	VectorRotation{VectorRotation2}
	bool constexpr operator!=(VectorRotation const& a, VectorRotation2 const& b){
		return !(a==b);
	}
	
}

#endif /* GEOMETRY_ROTATION_H */
