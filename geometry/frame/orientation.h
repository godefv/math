#ifndef GEOMETRY_OBJECT_FRAME_H
#define GEOMETRY_OBJECT_FRAME_H 

#include"../object/direction.h"
#include"../algebra/definition.h"
#include"../algebra/dot_product.h"
#include"../object/point.h"
#include"../point_transform/translation.h"
#include"../../group/morphism.h"
#include"../../hana.h"


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

	namespace internal{
		auto constexpr apply_direction_map=
			group::endomorphism(add_operation_t{}, 
			group::endomorphism(mult_operation_t{}, 
				[]<class OperandT, class DirectionMapT>(OperandT const& a, DirectionMapT const& direction_map){
					if constexpr(hana::find(DirectionMapT{}, OperandT{}) == hana::nothing){
						return a;
					}else{
						return direction_map[a];
					}
				}
			));

		auto constexpr transpose(auto const& direction_map){
			auto new_keys=direction_map
				|hana::values
				|hana::transform_with(get_reference_frame)
				|hana::fold_with(hana::union_)
				|hana::to_tuple;
			return hana::to_map(hana::zip_with(hana::make_pair
				,new_keys
				,hana::transform(new_keys, [&](auto new_key){
					auto project_new_key_on_this=[&](auto const& key_value){
						return project(hana::first(key_value)*(new_key|inverse(hana::second(key_value))), grades(hana::second(key_value)));
					};
					return direction_map
						|hana::to_tuple
						|hana::transform_with(project_new_key_on_this)
						|hana::fold_with(add_operation_t{});
				})
			));
		}
	}
	//orientation_t
	template<class DirectionMapT>
	struct orientation_t{
		//! vectors must be a map from directions of this frame to orthonormal vectors written in a parent frame
		DirectionMapT vectors;
	};
	template<class DirectionMapT>
	orientation_t(DirectionMapT const&)->orientation_t<DirectionMapT>;

	auto constexpr inverse(orientation_t<auto> const& orientation){
		return orientation_t{internal::transpose(orientation.vectors)};
	}

	template<MultiVector OperandT, class DirectionMapT>
		requires static_cast<bool>(hana::difference(
			 get_reference_frame(OperandT{})
			,hana::to_set(hana::keys(DirectionMapT{}))
			//TODO: allow partial frame change. For example, (X,Y)->(e1,e2) can be used to transform e3+X. Or do not allow it ?
		)==hana::make_set())
	auto constexpr change_reference_frame(OperandT const& operand, orientation_t<DirectionMapT> const& old_reference){
		return internal::apply_direction_map(operand, old_reference.vectors);
	}

	template<class Name>
	auto constexpr change_reference_frame(point_t<Name> const& operand, orientation_t<auto> const&){
		return operand;
	}
	template<class Name>
	auto constexpr change_reference_frame(transformed_point_t<Name,translation_t<auto>> const& operand, orientation_t<auto> const& old_reference){
		return transformed_point_t{operand.origin, translation_t{change_reference_frame(operand.transform.vector, old_reference)}};
	}
}

#endif /* GEOMETRY_OBJECT_FRAME_H */
