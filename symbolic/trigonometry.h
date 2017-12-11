#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H 

#include"operation.h"
#include"rational.h"
#include"../vector/basis.h"
#include"../vector/addition.h"

#include<iostream>

namespace symbolic{
	using pi_t=symbol_t<struct pi_symbol_name_t>;
	auto constexpr pi=pi_t{};
	auto constexpr eval(pi_t){return 3.14159265358979323846;}
	auto constexpr abs(pi_t const& a){return a;}

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

	//first quadrant exact values
	auto constexpr cos(vector::zero_t){return integer<1>;}
	auto constexpr cos(angle_t<ratio_t<1,6>>){return vector::basis_element_t{sqrt(integer<3>), ratio<1,2>};}
	auto constexpr cos(angle_t<ratio_t<1,5>>){return vector::add_operation_t::apply(integer<1>, vector::basis_element_t{sqrt(integer<5>), ratio<1,4>});}
	auto constexpr cos(angle_t<ratio_t<1,4>>){return vector::basis_element_t{sqrt(integer<2>), ratio<1,2>};}
	auto constexpr cos(angle_t<ratio_t<1,3>>){return ratio<1,2>;}
	auto constexpr cos(angle_t<ratio_t<1,2>>){return integer<0>;}
	auto constexpr cos(angle_t<ratio_t<3,5>>){return vector::add_operation_t::apply(integer<1>, -vector::basis_element_t{sqrt(integer<5>), ratio<1,4>});}
	//express every angle in terms of the corresponding first quadrant angle
	auto constexpr cos(NegativeAngle const& angle){
		return cos(-angle);
	}
	auto constexpr cos(PositiveAngleMoreThanHalfTurn const& angle){
		return cos(angle-angle_t<integer_t<2>>{});
	}
	auto constexpr cos(AngleQuadrant2 const& angle){
		return cos(angle_t<integer_t<1>>{}-angle);
	}
	//avoid problematic value of one half turn exactly
	auto constexpr cos(angle_t<integer_t<1>>){
		return integer<-1>;
	}

	//implement sin over cos
	auto constexpr sin(Angle const& angle){
		return cos(angle_t<ratio_t<1,2>>{}-angle);
	}
}

#endif /* TRIGONOMETRY_H */
