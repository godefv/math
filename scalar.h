#ifndef SCALAR_H
#define SCALAR_H 

#include"symbolic/rational.h"

#include<type_traits>
#include<ratio>

namespace vector{
	template<class T> struct scalar_wrapper_t{
		T value;
	};
	template<class T> scalar_wrapper_t(T a) -> scalar_wrapper_t<T>;

	//concepts
	template<class T> struct is_scalar_wrapper:std::false_type{};
	template<class T> struct is_scalar_wrapper<scalar_wrapper_t<T>>:std::true_type{};
	template<class T> concept bool SimpleScalar=std::is_arithmetic<T>::value || symbolic::Ratio<T>;
	template<class T> concept bool Scalar=SimpleScalar<T> || is_scalar_wrapper<T>::value;
	template<class T> concept bool Zero=symbolic::is_zero<T>::value;
	template<class T> concept bool NonZero=!symbolic::is_zero<T>::value;
	template<class T> concept bool NonZeroScalar=Scalar<T> && !Zero<T>;
}

#endif /* SCALAR_H */
