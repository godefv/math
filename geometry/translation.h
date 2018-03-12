#ifndef GEOMETRY_TRANSLATION_H
#define GEOMETRY_TRANSLATION_H 

#include"../vector/addition.h"

namespace geometry{
	//A translation is a vector
	template<class T> concept bool Translation=vector::Vector<T>;
}

#endif /* GEOMETRY_TRANSLATION_H */
