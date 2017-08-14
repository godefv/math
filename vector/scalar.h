#ifndef SCALAR_H
#define SCALAR_H 

#include<type_traits>
#include<ratio>

namespace vector{
	template<std::intmax_t Numerator, std::intmax_t Denominator>
	struct scalar_ratio_t: std::ratio<Numerator,Denominator>{
		constexpr operator double() const{return static_cast<double>(Numerator)/Denominator;}
	};

	//operators
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator*(scalar_ratio_t<N1,D1> a, scalar_ratio_t<N2,D2> b){
		using result_t=std::ratio_multiply<typename decltype(a)::type, typename decltype(b)::type>;
		return scalar_ratio_t<result_t::num, result_t::den>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator/(scalar_ratio_t<N1,D1> a, scalar_ratio_t<N2,D2> b){
		using result_t=std::ratio_divide<typename decltype(a)::type, typename decltype(b)::type>;
		return scalar_ratio_t<result_t::num, result_t::den>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator+(scalar_ratio_t<N1,D1> a, scalar_ratio_t<N2,D2> b){
		using result_t=std::ratio_add<typename decltype(a)::type, typename decltype(b)::type>;
		return scalar_ratio_t<result_t::num, result_t::den>{};
	}
	template<std::intmax_t N1, std::intmax_t D1, std::intmax_t N2, std::intmax_t D2>
	auto constexpr operator-(scalar_ratio_t<N1,D1> a, scalar_ratio_t<N2,D2> b){
		using result_t=std::ratio_subtract<typename decltype(a)::type, typename decltype(b)::type>;
		return scalar_ratio_t<result_t::num, result_t::den>{};
	}
	template<std::intmax_t N1, std::intmax_t D1>
	auto constexpr operator-(scalar_ratio_t<N1,D1>){
		return scalar_ratio_t<-N1, D1>{};
	}

	//variable templates
	template<std::intmax_t value>
	auto scalar=scalar_ratio_t<value, 1>{};

	template<std::intmax_t Numerator, std::intmax_t Denominator>
	auto scalar_ratio=scalar_ratio_t<Numerator, Denominator>{};
	
	//concepts
	template<class T> struct is_scalar_ratio: std::false_type{};
	template<std::intmax_t Numerator, std::intmax_t Denominator> 
	struct is_scalar_ratio<scalar_ratio_t<Numerator,Denominator>>: std::true_type{};
	template<class T> concept bool ScalarRatio=is_scalar_ratio<T>::value;

	template<class ScalarT> concept bool Scalar=std::is_arithmetic<ScalarT>::value || ScalarRatio<ScalarT>;
	
	template<class T> struct is_zero:std::false_type{};
	template<std::intmax_t Denominator> struct is_zero<scalar_ratio_t<0,Denominator>>:std::true_type{};
	template<class T> concept bool Zero=is_zero<T>::value;

	template<class T> concept bool NonZeroScalar=Scalar<T> && !Zero<T>;
}

#endif /* SCALAR_H */
