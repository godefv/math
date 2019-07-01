#ifndef SYMBOLIC_TRIGONOMETRY_H
#define SYMBOLIC_TRIGONOMETRY_H 

#include"all.h"
#include"../constant.h"
#include"../rational.h"
#include"../../vector.h"

#include<iostream>
#include<type_traits>

namespace godefv::math{
	template<class RatioT>
	using angle_t=decltype(pi*RatioT{});

	auto constexpr half_turn=angle_t<integer_t<1>>{};
	auto constexpr full_turn=angle_t<integer_t<2>>{};

	template<class T> concept bool Angle=Vector<T,pi_t>;

	auto constexpr turns(Angle const& angle){return ratio<1,2>*coordinate(pi, angle);}

	template<class T> concept bool NegativeAngle=Angle<T> && requires(T angle){{turns(angle)< integer<0>} -> std::true_type;};
	template<class T> concept bool PositiveAngle=Angle<T> && requires(T angle){{turns(angle)>=integer<0>} -> std::true_type;};
	template<class T> concept bool NegativeAngleMoreThanHalfTurn=NegativeAngle<T> && requires(T angle){{turns(angle)< ratio<-1,2>} -> std::true_type;};
	template<class T> concept bool PositiveAngleMoreThanHalfTurn=PositiveAngle<T> && requires(T angle){{turns(angle)>=ratio< 1,2>} -> std::true_type;};
	template<class T> concept bool AngleMoreThanHalfTurn=NegativeAngleMoreThanHalfTurn<T> || PositiveAngleMoreThanHalfTurn<T>;
	template<class T> concept bool AngleQuadrant1=PositiveAngle<T> && !AngleMoreThanHalfTurn<T> && requires(T angle){{turns(angle)< ratio< 1,4>} -> std::true_type;};
	template<class T> concept bool AngleQuadrant2=PositiveAngle<T> && !AngleMoreThanHalfTurn<T> && requires(T angle){{turns(angle)>=ratio< 1,4>} -> std::true_type;};
	template<class T> concept bool AngleQuadrant3=NegativeAngle<T> && !AngleMoreThanHalfTurn<T> && requires(T angle){{turns(angle)< ratio<-1,4>} -> std::true_type;};
	template<class T> concept bool AngleQuadrant4=NegativeAngle<T> && !AngleMoreThanHalfTurn<T> && requires(T angle){{turns(angle)>=ratio<-1,4>} -> std::true_type;};

	//first quadrant exact values
	auto constexpr cos(zero_t){return integer<1>;}
	auto constexpr cos(angle_t<ratio_t<1,6>>){return sqrt(integer<3>)*ratio<1,2>;}
	auto constexpr cos(angle_t<ratio_t<1,5>>){return integer<1>+sqrt(integer<5>)*ratio<1,4>;}
	auto constexpr cos(angle_t<ratio_t<1,4>>){return sqrt(integer<2>)*ratio<1,2>;}
	auto constexpr cos(angle_t<ratio_t<1,3>>){return ratio<1,2>;}
	auto constexpr cos(angle_t<ratio_t<1,2>>){return integer<0>;}
	auto constexpr cos(angle_t<ratio_t<3,5>>){return integer<1>+sqrt(integer<5>)*ratio<-1,4>;}
	//express every angle in terms of the corresponding first quadrant angle
	auto constexpr cos(NegativeAngle const& angle){
		return cos(-angle);
	}
	auto constexpr cos(PositiveAngleMoreThanHalfTurn const& angle){
		return cos(angle-full_turn);
	}
	auto constexpr cos(AngleQuadrant2 const& angle){
		return cos(half_turn-angle);
	}
	//avoid problematic value of one half turn exactly
	auto constexpr cos(angle_t<integer_t<1>>){
		return integer<-1>;
	}

	//implement sin over cos
	auto constexpr sin(Angle const& angle){
		return cos(angle_t<ratio_t<1,2>>{}-angle);
	}

	//cos²+sin²=1
	template<Symbol AngleT>
	auto constexpr operator+(square_t<operation_t<cos_t,AngleT>>
	                        ,square_t<operation_t<cos_t,decltype(angle_t<ratio_t<1,2>>{}-AngleT{})>>){
		return integer<1>;
	}
	//ch²-sh²=1
	template<Symbol AngleT>
	auto constexpr operator+(        square_t<operation_t<cosh_t,AngleT>>
	                        ,minus_t<square_t<operation_t<sinh_t,AngleT>>>){
		return integer<1>;
	}
	//cos(x)cos(y)-sin(x)sin(y)=cos(x+y)
	template<Symbol Angle1, Symbol Angle2>
	auto constexpr operator+(group::generated_by_operation_t<mult_operation_t
	                        ,operation_t<cos_t,Angle1>
	                        ,operation_t<cos_t,Angle2>>
							,minus_t<group::generated_by_operation_t<mult_operation_t
	                        ,operation_t<cos_t,decltype(angle_t<ratio_t<1,2>>{}-Angle1{})>
	                        ,operation_t<cos_t,decltype(angle_t<ratio_t<1,2>>{}-Angle2{})>>>){
		return cos(Angle1{}+Angle2{});
	}
	//cos(x)sin(y)+sin(x)cos(y)=sin(x+y)
	template<Symbol Angle1, Symbol Angle2>
	auto constexpr operator+(group::generated_by_operation_t<mult_operation_t
	                        ,operation_t<cos_t,Angle1>
	                        ,operation_t<cos_t,decltype(angle_t<ratio_t<1,2>>{}-Angle2{})>>
							,group::generated_by_operation_t<mult_operation_t
	                        ,operation_t<cos_t,Angle2>
	                        ,operation_t<cos_t,decltype(angle_t<ratio_t<1,2>>{}-Angle1{})>>){
		return sin(Angle1{}+Angle2{});
	}
	//cos(x)²-sin(x)²=cos(2x)
	template<Symbol AngleT>
	auto constexpr operator+(square_t<operation_t<cos_t,AngleT>>
	                        ,minus_t<square_t<operation_t<cos_t,decltype(angle_t<ratio_t<1,2>>{}-AngleT{})>>>){
		return cos(integer<2>*AngleT{});
	}
	//cos(x)sin(x)=sin(2x)/2
	template<Symbol AngleT>
	auto constexpr operator*(operation_t<cos_t,AngleT>
	                        ,operation_t<cos_t,decltype(angle_t<ratio_t<1,2>>{}-AngleT{})>){
		return ratio<1,2>*sin(integer<2>*AngleT{});
	}
}

#endif /* SYMBOLIC_TRIGONOMETRY_H */
