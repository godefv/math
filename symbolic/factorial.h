#ifndef FACTORIAL_H
#define FACTORIAL_H 

#include"rational.h"

namespace symbolic{
	auto constexpr factorial(integer_t<1>){
		return 1;
	}
	auto constexpr factorial(Integer i){
		return i*factorial(i-1);
	}
}

#endif /* FACTORIAL_H */
