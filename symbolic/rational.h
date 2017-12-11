#ifndef RATIONAL_H
#define RATIONAL_H 

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

	//eval
	template<std::intmax_t N>
	auto constexpr eval(integer_t<N> const&){return N;}
	auto constexpr eval(Ratio const& a){return static_cast<double>(a);}

	//inverse
	auto constexpr inverse(Ratio a){
		using type=typename decltype(a)::type;
		return ratio_t<type::den,type::num>{};
	}

	//operators
	auto constexpr operator*(double a, Ratio b){return a*eval(b);}
	auto constexpr operator*(Ratio a, double b){return eval(a)*b;}
	Ratio{Ratio2}
	auto constexpr operator*(Ratio a, Ratio2 b){
		using result_t=std::ratio_multiply<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio_t<result_t::num, result_t::den>{};
	}
	Ratio{Ratio2}
	auto constexpr operator/(Ratio a, Ratio2 b){
		using result_t=std::ratio_divide<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio_t<result_t::num, result_t::den>{};
	}
	Ratio{Ratio2}
	auto constexpr operator+(Ratio a, Ratio2 b){
		using result_t=std::ratio_add<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio_t<result_t::num, result_t::den>{};
	}
	Ratio{Ratio2}
	auto constexpr operator-(Ratio a, Ratio2 b){
		using result_t=std::ratio_subtract<typename decltype(a)::type, typename decltype(b)::type>;
		return ratio_t<result_t::num, result_t::den>{};
	}
	template<std::intmax_t N1, std::intmax_t D1>
	auto constexpr operator-(ratio_t<N1,D1>){
		return ratio_t<-N1, D1>{};
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
	template<std::intmax_t N1, std::intmax_t D1>
	std::ostream& operator<<(std::ostream& out, ratio_t<N1,D1>){
		return out<<N1<<"/"<<D1;
	}

	//abs
	auto constexpr abs(Ratio a){
		using type=typename decltype(a)::type;
		return ratio_t<(type::num>0)?type::num:-type::num,type::den>{};
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
		return ratio_t<rounded_sqrt(N),rounded_sqrt(D)>{};
	}
}

#endif /* RATIONAL_H */
