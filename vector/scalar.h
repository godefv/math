#ifndef SCALAR_H
#define SCALAR_H 

#include"../symbolic/rational.h"

#include<type_traits>
#include<ratio>

namespace vector{
	template<class T> struct scalar_wrapper_t{
		T value;
	};
	template<class T> scalar_wrapper_t(T a) -> scalar_wrapper_t<T>;

	//concepts
	template<class T> concept bool SimpleScalar=std::is_arithmetic<T>::value || symbolic::Ratio<T>;
	//template<class T> concept bool BasisVectorScalar=vector::BasisVector<T> && requires(T vector){
		//requires SimpleScalar<decltype(vector.element)>;
	//};
	//template<class T> concept bool VectorScalar=BasisVectorScalar<T> || 
		//(Vector<T> && requires(T vector){
			//requires VectorScalar<decltype(vector.first)>;
			//requires VectorScalar<decltype(vector.second)>;
		//});
	template<class T> concept bool Scalar=SimpleScalar<T>;// || VectorScalar<T>;
	template<class T> concept bool Zero=symbolic::is_zero<T>::value;
	template<class T> concept bool NonZero=!symbolic::is_zero<T>::value;
	template<class T> concept bool NonZeroScalar=Scalar<T> && !Zero<T>;
}

#endif /* SCALAR_H */
