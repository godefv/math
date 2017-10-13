#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H 

#include"rational.h"
#include"../vector/basis.h"
#include"../vector/addition.h"

#include<iostream>

namespace symbolic{
	struct pi_t{
		auto constexpr value() const{return 3.14159265358979323846;}
		constexpr operator double() const{return value();}
	};
	auto constexpr pi=pi_t{};
	auto constexpr eval(pi_t const& a){return a.value();}

	inline std::ostream& operator<<(std::ostream& out, pi_t){
		return out<<"pi";
	}

	template<class RatioT>
	using angle_t=decltype(vector::basis_element(pi_t{},RatioT{}));

	auto constexpr half_turn=angle_t<integer_t<1>>{};

	inline std::ostream& operator<<(std::ostream& out, angle_t<auto> const& angle){
		return out<<angle.coordinate<<" half-turn";
	}

	template<class T> concept bool Angle=vector::Vector<T> && requires(T angle){{angle.element} -> pi_t;};
	template<class T> concept bool NegativeAngle=Angle<T> && requires(T angle){{angle.coordinate< integer<0>} -> std::true_type;};
	template<class T> concept bool PositiveAngle=Angle<T> && requires(T angle){{angle.coordinate>=integer<0>} -> std::true_type;};
	template<class T> concept bool NegativeAngleMoreThanHalfTurn=NegativeAngle<T> && requires(T angle){{angle.coordinate< integer<-1>} -> std::true_type;};
	template<class T> concept bool PositiveAngleMoreThanHalfTurn=PositiveAngle<T> && requires(T angle){{angle.coordinate>=integer< 1>} -> std::true_type;};
	template<class T> concept bool AngleMoreThanHalfTurn=NegativeAngleMoreThanHalfTurn<T> || PositiveAngleMoreThanHalfTurn<T>;
	template<class T> concept bool AngleQuadrant1=PositiveAngle<T> && !AngleMoreThanHalfTurn<T> && requires(T angle){{angle.coordinate< ratio< 1,2>} -> std::true_type;};
	template<class T> concept bool AngleQuadrant2=PositiveAngle<T> && !AngleMoreThanHalfTurn<T> && requires(T angle){{angle.coordinate>=ratio< 1,2>} -> std::true_type;};
	template<class T> concept bool AngleQuadrant3=NegativeAngle<T> && !AngleMoreThanHalfTurn<T> && requires(T angle){{angle.coordinate< ratio<-1,2>} -> std::true_type;};
	template<class T> concept bool AngleQuadrant4=NegativeAngle<T> && !AngleMoreThanHalfTurn<T> && requires(T angle){{angle.coordinate>=ratio<-1,2>} -> std::true_type;};

	auto constexpr cos(vector::zero_t){return integer<1>;}
	auto constexpr cos(angle_t<ratio_t<1,2>>){return integer<0>;}
	auto constexpr cos(angle_t<integer_t<1>>){return integer<-1>;}
	auto constexpr cos(NegativeAngle const& angle){
		return cos(-angle);
	}
	auto constexpr cos(PositiveAngleMoreThanHalfTurn const& angle){
		return cos(angle-angle_t<integer_t<2>>{});
	}
	auto constexpr cos(AngleQuadrant2 const& angle){
		return cos(angle_t<integer_t<1>>{}-angle);
	}

	auto constexpr sin(auto const& angle){
		return cos(angle_t<ratio_t<1,2>>{}-angle);
	}
}

#endif /* TRIGONOMETRY_H */
