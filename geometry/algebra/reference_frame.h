#ifndef GODEFV_MATH_GEOMETRY_REFERENCE_FRAME_H
#define GODEFV_MATH_GEOMETRY_REFERENCE_FRAME_H 

#include"../object/direction.h"
#include"../../group/morphism.h"
#include"../../addition/operation.h"
#include"../../multiplication/operation.h"
#include"../../hana.h"

#include<type_traits>

namespace godefv::math::geometry{
	namespace hana=boost::hana;

	auto constexpr get_reference_frame=
		group::morphism_t{add_operation_t{}, hana::union_,
		group::morphism_t{mult_operation_t{}, hana::union_, 
			[](auto const& a){
				if constexpr(Direction<std::decay_t<decltype(a)>>){
					return hana::make_set(a);
				}else{
					return hana::make_set();
				}
			}
		}};

}

#endif /* GODEFV_MATH_GEOMETRY_REFERENCE_FRAME_H */
