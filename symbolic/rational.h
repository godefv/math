#ifndef RATIONAL_H
#define RATIONAL_H 

#include"symbol.h"
#include<iostream>
#include<ratio>
#include<type_traits>

namespace symbolic{
	template<std::intmax_t Numerator, std::intmax_t Denominator>
	struct ratio_t: std::ratio<Numerator,Denominator>{
		constexpr operator double() const{return static_cast<double>(Numerator)/Denominator;}
		auto constexpr numerator(){return Numerator;}
		auto constexpr denominator(){return Denominator;}
	};

	template<std::intmax_t value>
	using integer_t=ratio_t<value, 1>;

	//variable templates
	template<std::intmax_t value>
	auto integer=integer_t<value>{};

	template<std::intmax_t Numerator, std::intmax_t Denominator>
	auto ratio=ratio_t<Numerator, Denominator>{};
	
	//concepts
	template<std::intmax_t Numerator, std::intmax_t Denominator> 
	struct is_symbol<ratio_t<Numerator,Denominator>>: std::true_type{};

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

	//eval
	template<std::intmax_t N>
	auto constexpr eval(integer_t<N> const&){return N;}
	auto constexpr eval(Ratio const& a){return static_cast<double>(a);}

	//inverse
	auto constexpr inverse(Ratio a){
		return ratio<a.denominator(),a.numerator()>;
	}

	//operators
	auto constexpr operator*(double a, Ratio b){return a*eval(b);}
	auto constexpr operator*(Ratio a, double b){return eval(a)*b;}
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
	Ratio{Ratio2}
	auto constexpr operator+(Ratio a, Ratio2 b){
		using result_t=std::ratio_add<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio<result_t::num, result_t::den>;
	}
	Ratio{Ratio2}
	auto constexpr operator-(Ratio a, Ratio2 b){
		using result_t=std::ratio_subtract<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio<result_t::num, result_t::den>;
	}
	auto constexpr operator-(Ratio a){
		return ratio<-a.numerator(), a.denominator()>;
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

	//abs
	auto constexpr abs(Ratio a){
		return ratio<(a.numerator()>0)?a.numerator():-a.numerator(),a.denominator()>;
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
	Ratio{Ratio2} int constexpr static_compare(Ratio const& a, Ratio2 const& b){return (a-b).numerator();}
}

#endif /* RATIONAL_H */
