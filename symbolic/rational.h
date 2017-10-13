#ifndef RATIONAL_H
#define RATIONAL_H 

#include"operation.h"
#include<iostream>
#include<ratio>
#include<type_traits>

namespace symbolic{
	template<std::intmax_t Numerator, std::intmax_t Denominator>
	struct ratio_t: std::ratio<Numerator,Denominator>{
		constexpr operator double() const{return static_cast<double>(Numerator)/Denominator;}
	};

	template<std::intmax_t value>
	using integer_t=ratio_t<value, 1>;

	//variable templates
	template<std::intmax_t value>
	auto integer=integer_t<value>{};

	template<std::intmax_t Numerator, std::intmax_t Denominator>
	auto ratio=ratio_t<Numerator, Denominator>{};
	
	//eval
	template<std::intmax_t N1, std::intmax_t D1>
	auto constexpr eval(ratio_t<N1,D1> const& a){return static_cast<double>(a);}

	//abs
	template<std::intmax_t N1, std::intmax_t D1>
	auto constexpr abs(ratio_t<N1,D1> a){
		using type=typename decltype(a)::type;
		return ratio_t<(type::num>0)?type::num:-type::num,type::den>{};
	}

	//nth_root
	template<std::intmax_t N>
	auto constexpr nth_root(integer_t<1> a){
		return a;
	}

	//operators
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator*(ratio_t<N1,D1> a, ratio_t<N2,D2> b){
		using result_t=std::ratio_multiply<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio_t<result_t::num, result_t::den>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator/(ratio_t<N1,D1> a, ratio_t<N2,D2> b){
		using result_t=std::ratio_divide<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio_t<result_t::num, result_t::den>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator+(ratio_t<N1,D1> a, ratio_t<N2,D2> b){
		using result_t=std::ratio_add<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio_t<result_t::num, result_t::den>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator-(ratio_t<N1,D1> a, ratio_t<N2,D2> b){
		using result_t=std::ratio_subtract<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio_t<result_t::num, result_t::den>{};
	}
	template<std::intmax_t N1, std::intmax_t D1>
	auto constexpr operator-(ratio_t<N1,D1>){
		return ratio_t<-N1, D1>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator<(ratio_t<N1,D1> a, ratio_t<N2,D2> b){
		return std::ratio_less<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator>(ratio_t<N1,D1> a, ratio_t<N2,D2> b){
		return std::ratio_greater<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator<=(ratio_t<N1,D1> a, ratio_t<N2,D2> b){
		return std::ratio_less_equal<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator>=(ratio_t<N1,D1> a, ratio_t<N2,D2> b){
		return std::ratio_greater_equal<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator==(ratio_t<N1,D1> a, ratio_t<N2,D2> b){
		return std::ratio_equal<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator!=(ratio_t<N1,D1> a, ratio_t<N2,D2> b){
		return std::ratio_not_equal<typename decltype(a)::type, typename decltype(b)::type>{};
	}
	template<std::intmax_t N1, std::intmax_t D1>
	std::ostream& operator<<(std::ostream& out, ratio_t<N1,D1>){
		return out<<N1<<"/"<<D1;
	}

	//concepts
	template<class T> struct is_ratio: std::false_type{};
	template<std::intmax_t Numerator, std::intmax_t Denominator> 
	struct is_ratio<ratio_t<Numerator,Denominator>>: std::true_type{};
	template<class T> concept bool Ratio=is_ratio<T>::value;

	template<class T> concept bool RatioLessThanOne=Ratio<T> && std::ratio_less<T,integer_t<1>>::value;

	template<class T> struct is_integer:std::false_type{};
	template<std::intmax_t Numerator> struct is_integer<ratio_t<Numerator,1>>:std::true_type{};
	template<class T> concept bool Integer=is_integer<T>::value;

	template<class T> struct is_zero:std::false_type{};
	template<std::intmax_t Denominator> struct is_zero<ratio_t<0,Denominator>>:std::true_type{};
	template<class T> concept bool Zero=is_zero<T>::value;
}

#endif /* RATIONAL_H */
