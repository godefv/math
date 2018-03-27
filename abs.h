#ifndef ABS_H
#define ABS_H 

#include<type_traits>

namespace math{
	template<class T> requires std::is_arithmetic<T>::value
	auto constexpr abs(T const& a){
		return a>0?a:-a;
	}
}

#endif /* ABS_H */
