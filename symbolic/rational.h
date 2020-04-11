#ifndef RATIONAL_H
#define RATIONAL_H 

#include"symbol.h"
#include"../scalar.h"
#include"../eval.h"

#include<iostream>
#include<ratio>
#include<type_traits>
#include<limits>

namespace godefv::math{
	template<std::intmax_t Numerator, std::intmax_t Denominator> requires Denominator>=0
	struct ratio_t: std::ratio<Numerator,Denominator>{
		constexpr operator double() const requires Denominator>1 {
			return static_cast<double>(Numerator)/Denominator;
		}
		//integers should be cast to an integral type
		//zero should not be cast at all : it should either be used directly or be optimized out
		constexpr operator std::intmax_t() const requires Denominator==1 && Numerator!=0 &&
		!( Numerator>std::numeric_limits<int>::min() 
		&& Numerator<std::numeric_limits<int>::max())
		{
			return Numerator;
		}
		constexpr operator int() const requires Denominator==1 && Numerator!=0 &&
		(  Numerator>std::numeric_limits<int>::min() 
		&& Numerator<std::numeric_limits<int>::max())
		{
			return static_cast<int>(Numerator);
		}
		auto constexpr numerator()   const{return Numerator;}
		auto constexpr denominator() const{return Denominator;}
	};

	template<std::intmax_t value>
	using integer_t=ratio_t<value, 1>;

	//variable templates
	template<std::intmax_t value>
	auto integer=integer_t<value>{};

	template<std::intmax_t Numerator, std::intmax_t Denominator>
	auto ratio=ratio_t<Numerator, Denominator>{};
	
	//concepts
	template<class T> struct is_ratio: std::false_type{};
	template<std::intmax_t Numerator, std::intmax_t Denominator> 
	struct is_ratio<ratio_t<Numerator,Denominator>>: std::true_type{};
	template<class T> concept bool Ratio=is_ratio<T>::value;

	template<class T> concept bool RatioLessThanOne=Ratio<T> && std::ratio_less<T,integer_t<1>>::value;

	template<class T> struct is_static_integer:std::false_type{};
	template<std::intmax_t Numerator> struct is_static_integer<ratio_t<Numerator,1>>:std::true_type{};
	template<class T> concept bool StaticInteger=is_static_integer<T>::value;
	template<class T> concept bool Integer=is_static_integer<T>::value || std::is_integral<T>::value;

	template<class T> struct is_zero:std::false_type{};
	template<std::intmax_t Denominator> struct is_zero<ratio_t<0,Denominator>>:std::true_type{};
	template<class T> concept bool Zero=is_zero<T>::value;
	template<class T> concept bool NonZero=!is_zero<T>::value;
	template<class T> concept bool NonZeroRatio=Ratio<T> && !Zero<T>;
	template<class T> concept bool NonZeroScalar=Scalar<T> && !Zero<T>;
	template<class T> concept bool NonZeroInteger=Integer<T> && !Zero<T>;
	template<class T> concept bool PositiveScalar=Scalar<T> && requires(T x){{x>=integer<0>}->std::true_type;};

	template<Ratio RatioT> struct is_simple_scalar<RatioT>:std::true_type{};
	template<Ratio RatioT> struct is_symbol<RatioT>: std::true_type{};

	//eval
	template<std::intmax_t N>
	auto constexpr eval_with_data(integer_t<N> const&, auto const&){return N;}
	auto constexpr eval_with_data(Ratio const& a, auto const&){return static_cast<double>(a);}

	//operators
	auto constexpr operator*(Number, Zero){return integer<0>;}
	auto constexpr operator*(Zero, Number){return integer<0>;}
	Ratio{Ratio2}
	auto constexpr operator*(Ratio a, Ratio2 b){
		using result_t=std::ratio_multiply<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio<result_t::num, result_t::den>;
	}
	Ratio{Ratio2}
	auto constexpr operator/(Ratio a, Ratio2 b){
		using result_t=std::ratio_divide<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio<result_t::num, result_t::den>;
	}
	auto constexpr operator/(Number a, NonZeroRatio b){return a/eval(b);}
	auto constexpr operator/(NonZeroRatio a, Number b){return eval(a)/b;}
	auto constexpr operator/(Zero, Number){return integer<0>;}
	Ratio{Ratio2}
	auto constexpr operator+(Ratio a, Ratio2 b){
		using result_t=std::ratio_add<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio<result_t::num, result_t::den>;
	}
	auto constexpr operator+(Number a, NonZeroRatio b){return a+eval(b);}
	auto constexpr operator+(NonZeroRatio a, Number b){return eval(a)+b;}
	Ratio{Ratio2}
	auto constexpr operator-(Ratio a, Ratio2 b){
		using result_t=std::ratio_subtract<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio<result_t::num, result_t::den>;
	}
	auto constexpr operator-(Ratio a){
		return integer<0>-a;
	}
	Ratio{Ratio2}
	auto constexpr operator<(Ratio a, Ratio2 b){
		return std::ratio_less<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	Ratio{Ratio2}
	auto constexpr operator>(Ratio a, Ratio2 b){
		return std::ratio_greater<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	Ratio{Ratio2}
	auto constexpr operator<=(Ratio a, Ratio2 b){
		return std::ratio_less_equal<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	Ratio{Ratio2}
	auto constexpr operator>=(Ratio a, Ratio2 b){
		return std::ratio_greater_equal<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	Ratio{Ratio2}
	auto constexpr operator==(Ratio a, Ratio2 b){
		return std::ratio_equal<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	Ratio{Ratio2}
	auto constexpr operator!=(Ratio a, Ratio2 b){
		return std::ratio_not_equal<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	std::ostream& operator<<(std::ostream& out, Ratio a){
		return out<<a.numerator()<<"/"<<a.denominator();
	}
	template<class T> requires std::is_arithmetic<T>::value && !std::is_signed<T>::value
	auto constexpr operator>=(T a, integer_t<0>){return std::true_type{};}
	template<class NameT> requires Scalar<decltype(eval(symbol_t<NameT>{}))> && eval(symbol_t<NameT>{})>=0
	auto constexpr operator>=(symbol_t<NameT>, integer_t<0>){return std::true_type{};}

	//inverse
	auto constexpr inverse(Ratio a){
		return integer<1>/a;
	}

	//nth_root
	template<Ratio>	auto constexpr pow(integer_t<1> a){
		return a;
	}

	auto constexpr rounded_sqrt_impl(std::uintmax_t x, std::uintmax_t lo, std::uintmax_t hi)
	{
		auto mid=(lo+hi+1)/2;
		if(lo==hi){
			return lo;
		}else if(x<mid*mid){
			return rounded_sqrt_impl(x, lo, mid - 1);
		}else{
			return rounded_sqrt_impl(x, mid, hi);
		}
	};
	auto constexpr rounded_sqrt(std::uintmax_t x){
		return rounded_sqrt_impl(x, 0, x / 2 + 1);
	}

	template<std::intmax_t N, std::intmax_t D> requires rounded_sqrt(N)*rounded_sqrt(N)==N && rounded_sqrt(D)*rounded_sqrt(D)==D 
	auto constexpr sqrt(ratio_t<N,D>){
		return ratio<rounded_sqrt(N),rounded_sqrt(D)>;
	}

	//static_order
	Ratio{Ratio2} int constexpr static_compare(Ratio const& a, Ratio2 const& b){return (b-a).numerator();}
}

#endif /* RATIONAL_H */
