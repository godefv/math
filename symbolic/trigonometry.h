#ifndef SYMBOLIC_TRIGONOMETRY_H
#define SYMBOLIC_TRIGONOMETRY_H 

#include"symbol.h"
#include"rational.h"
#include"operation/all.h"
#include"../vector.h"

#include<iostream>
#include<type_traits>

namespace math{
	auto constexpr pi="π"_symbol;
	using pi_t=std::decay_t<decltype(pi)>;
	auto constexpr eval(pi_t){return 3.14159265358979323846;}
	auto constexpr abs(pi_t const& a){return a;}

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
	//template<class AngleT, class SinT> is_sin

	//cos²+sin²=1
	template<class Func2AngleT, class FuncT, Symbol AngleT> concept bool Func2Angle=
		   Vector<Func2AngleT, square_t<operation_t<FuncT,AngleT>> > 
		&& Symbol<decltype(coordinate(square_t<operation_t<FuncT,AngleT>>{}, Func2AngleT{}))>
		;
	template<class Cos2T, class Sin2T, Symbol AngleT> concept bool Cos2Sin2=
		      Func2Angle<Cos2T,cos_t,AngleT>
		&& ( (Func2Angle<Sin2T,sin_t,AngleT                                    > && coordinate(square_t<operation_t<sin_t,AngleT                                    >>{}, Sin2T{})==coordinate(square_t<operation_t<cos_t,AngleT>>{}, Cos2T{})) 
		   ||(Func2Angle<Sin2T,cos_t,decltype(angle_t<ratio_t<1,2>>{}-AngleT{})> && coordinate(square_t<operation_t<cos_t,decltype(angle_t<ratio_t<1,2>>{}-AngleT{})>>{}, Sin2T{})==coordinate(square_t<operation_t<cos_t,AngleT>>{}, Cos2T{})) 
		   );
	//Cos2Sin2{Cos2T, Sin2T, AngleT} <= alas, AngleT cannot be deduced
	//auto constexpr operator+(Cos2T, Sin2T){
		//return coordinate(sqare_t<operation_t<cos_t,AngleT>>{}, Cos2T{});
	//}
	template<Symbol AngleT>
	auto constexpr operator+(square_t<operation_t<cos_t,AngleT>>
	                        ,square_t<operation_t<cos_t,decltype(angle_t<ratio_t<1,2>>{}-AngleT{})>>){
		return integer<1>;
	}
	template<Symbol AngleT, Symbol SymbolT>
	auto constexpr operator+(group::generated_by_operation_t<mult_operation_t, SymbolT, square_t<operation_t<cos_t,AngleT>> >
	                        ,group::generated_by_operation_t<mult_operation_t, SymbolT, square_t<operation_t<cos_t,decltype(angle_t<ratio_t<1,2>>{}-AngleT{})>> >){
		return SymbolT{};
	}
	template<Symbol AngleT, Symbol SymbolT>
	auto constexpr operator+(group::generated_by_operation_t<mult_operation_t, square_t<operation_t<cos_t,AngleT                                    >>, SymbolT >
	                        ,group::generated_by_operation_t<mult_operation_t, square_t<operation_t<cos_t,decltype(angle_t<ratio_t<1,2>>{}-AngleT{})>>, SymbolT >){
		return SymbolT{};
	}
	//ch²-sh²=1
	template<Symbol AngleT>
	auto constexpr operator+(        square_t<operation_t<cosh_t,AngleT>>
	                        ,minus_t<square_t<operation_t<sinh_t,AngleT>>>){
		return integer<1>;
	}
	template<Symbol AngleT, Symbol SymbolT>
	auto constexpr operator+(        group::generated_by_operation_t<mult_operation_t, SymbolT, square_t<operation_t<cosh_t,AngleT>> >
	                        ,minus_t<group::generated_by_operation_t<mult_operation_t, SymbolT, square_t<operation_t<sinh_t,AngleT>> >>){
		return SymbolT{};
	}
	template<Symbol AngleT, Symbol SymbolT>
	auto constexpr operator+(        group::generated_by_operation_t<mult_operation_t, square_t<operation_t<cosh_t,AngleT>>, SymbolT >
	                        ,minus_t<group::generated_by_operation_t<mult_operation_t, square_t<operation_t<sinh_t,AngleT>>, SymbolT >>){
		return SymbolT{};
	}
}

#endif /* SYMBOLIC_TRIGONOMETRY_H */
