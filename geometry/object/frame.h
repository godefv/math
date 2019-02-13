#ifndef GEOMETRY_OBJECT_FRAME_H
#define GEOMETRY_OBJECT_FRAME_H 

#include"point.h"
#include"direction.h"
#include"../vector_transform/projection.h"
#include"../algebra/dot_product.h"
#include"../../group/morphism.h"
#include"../../hana.h"


namespace math::geometry{
	auto constexpr get_frame=
		group::morphism_t{add_operation_t{}, boost::hana::union_,
		group::morphism_t{mult_operation_t{}, boost::hana::union_, 
			[](auto const& a){
				if constexpr(Direction<std::decay_t<decltype(a)>>){
					return boost::hana::make_set(a);
				}else{
					return boost::hana::make_set();
				}
			}
		}};

	namespace internal{
		auto constexpr apply_orientation=
			group::endomorphism(add_operation_t{}, 
			group::endomorphism(mult_operation_t{}, 
				[](auto const& a, auto const& direction_map){
					if constexpr(hana::find(direction_map, a) == hana::nothing){
						return a;
					}else{
						return direction_map[a];
					}
				}
			));

		auto constexpr transpose(auto const& direction_map){
			auto new_keys=direction_map
				|boost::hana::values
				|boost::hana::transform_with(get_frame)
				|boost::hana::fold_with(boost::hana::union_)
				|boost::hana::to_tuple;
			return boost::hana::to_map(boost::hana::zip_with(boost::hana::make_pair
				,new_keys
				,boost::hana::transform(new_keys, [&](auto new_key){
					auto project_new_key_on_this=[&](auto const& operand){
						return project(boost::hana::first(operand)*(inverse(new_key)|boost::hana::second(operand)), grades(boost::hana::second(operand)));
					};
					return direction_map
						|boost::hana::to_tuple
						|boost::hana::transform_with(project_new_key_on_this)
						|boost::hana::fold_with(add_operation_t{});
				})
			));
		}
	}
	//orientation_t
	template<class DirectionMapT>
	struct orientation_t{
		DirectionMapT vectors;

		//! vectors_ must be a map from directions of this frame to orthonormal vectors written in a parent frame
		explicit constexpr orientation_t(DirectionMapT&& vectors_)
			:vectors{std::forward<DirectionMapT>(vectors_)}
		{}

		auto constexpr convert_from_this_to_parent_frame(auto const& operand){
			return internal::apply_orientation(operand, vectors);
		}
	};

	auto constexpr inverse(orientation_t<auto> const& orientation){
		return orientation_t{internal::transpose(orientation.vectors)};
	}
}

#endif /* GEOMETRY_OBJECT_FRAME_H */
