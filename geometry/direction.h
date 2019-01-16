#ifndef GEOMETRY_DIRECTION_H
#define GEOMETRY_DIRECTION_H 

#include"../name.h"

namespace math::geometry{
	//concept
	template<class> struct is_direction:std::false_type{};
	template<class T> concept bool Direction=is_direction<T>::value;

	template<class F> concept bool DirectionTransform=requires(F f, direction_t direction){
		requires Direction<decltype(f(direction))>;
	};

	//direction
	template<class Name>
	class direction_t{
		Name name;
	};
	template<class Name>
	struct is_direction<direction_t<Name>>:std::true_type{};

	//transformed direction
	template<class Name, class DirectionTransformT>
	struct transformed_direction_t{
		direction_t<Name> origin;
		DirectionTransformT transform;
	};
	template<class Name, class DirectionTransformT>
	struct is_direction<transformed_direction_t<Name,DirectionTransformT>>:std::true_type{};
}


#endif /* GEOMETRY_DIRECTION_H */
