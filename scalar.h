#ifndef SCALAR_H
#define SCALAR_H 

#include"symbolic/rational.h"

#include<type_traits>
#include<ratio>

namespace math{
	template<class T> struct scalar_wrapper_t{
		T value;
	};
	template<class T> scalar_wrapper_t(T a) -> scalar_wrapper_t<T>;

	//concepts
	template<class T> struct is_scalar_wrapper:std::false_type{};
	template<class T> struct is_scalar_wrapper<scalar_wrapper_t<T>>:std::true_type{};

	template<class T> concept bool SimpleScalar=std::is_arithmetic<T>::value || Ratio<T>;

	template<class T> struct is_scalar:std::false_type{};
	template<class T> requires SimpleScalar<T> || is_scalar_wrapper<T>::value
	struct is_scalar<T>:std::true_type{};
	template<class T> concept bool Scalar=is_scalar<T>::value;
	template<class T> concept bool Zero=is_zero<T>::value;
	template<class T> concept bool NonZero=!is_zero<T>::value;
	template<class T> concept bool NonZeroScalar=Scalar<T> && !Zero<T>;
}

#endif /* SCALAR_H */
