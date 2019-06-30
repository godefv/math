#ifndef GODEFV_MATH_GEOMETRY_OBJECT_FRAME_H
#define GODEFV_MATH_GEOMETRY_OBJECT_FRAME_H 

#include"reference.h"
#include"../algebra/definition.h"
#include"../algebra/dot_product.h"
#include"../object/point.h"
#include"../point_transform/translation.h"
#include"../vector_transform/rotation.h"


namespace godefv::math::geometry{
	namespace hana=boost::hana;

	namespace internal{
		auto constexpr apply_direction_map=
			group::endomorphism(add_operation_t{}, 
			group::endomorphism(mult_operation_t{}, 
				[]<class OperandT, class DirectionMapT>(OperandT const& a, DirectionMapT const& direction_map){
					if constexpr(!hana::Hashable<hana::tag_of_t<OperandT>>::value){
						return a;
					}else{ 
						auto value=hana::find(DirectionMapT{}, OperandT{});
						if constexpr(value==hana::nothing){
							return a;
						}else{
							return direction_map[a];
						}
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
	//linear_map_t
	template<class DirectionMapT>
	struct linear_map_t{
		//! vectors must be a map from directions of this frame to orthonormal vectors written in a parent frame
		DirectionMapT vectors;
	};
	template<class DirectionMapT>
	linear_map_t(DirectionMapT const&)->linear_map_t<DirectionMapT>;

	//operators
	auto constexpr operator==(linear_map_t<auto> const& a, linear_map_t<auto> const& b){
		return a.vectors==b.vectors;
	}
	auto constexpr operator!=(linear_map_t<auto> const& a, linear_map_t<auto> const& b){
		return !(a==b);
	}
	std::ostream& operator<<(std::ostream& out, linear_map_t<auto> const& operand){
		out<<"linear_map{";
		hana::for_each(hana::to_tuple(operand.vectors), [&](auto const& key_value){
			out<<hana::first(key_value)<<":="<<hana::second(key_value)<<" ; ";
		});
		return out<<"}";
	}

	//
	auto constexpr inverse(linear_map_t<auto> const& orientation){
		return linear_map_t{internal::transpose(orientation.vectors)};
	}

	template<MultiVector OperandT, class DirectionMapT>
		requires static_cast<bool>(hana::is_subset(
			get_reference_frame(OperandT{}), hana::to_set(hana::keys(DirectionMapT{}))
		))
			//TODO: allow partial frame change. For example, (X,Y)->(e1,e2) can be used to transform e3+X. Or do not allow it ?
	auto constexpr change_reference_frame(OperandT const& operand, linear_map_t<DirectionMapT> const& old_reference){
		return internal::apply_direction_map(operand, old_reference.vectors);
	}

	template<class Name>
	auto constexpr change_reference_frame(point_t<Name> const& operand, linear_map_t<auto> const&){
		return operand;
	}
	auto constexpr change_reference_frame(translation_t<auto> const& operand, linear_map_t<auto> const& old_reference){
		return translation_t{change_reference_frame(operand.vector, old_reference)};
	}
	template<Vector... DirectionTypes>
	auto constexpr change_reference_frame(slice_t<DirectionTypes...> const& operand, linear_map_t<auto> const& old_reference){
		return slice_t{change_reference_frame(boost::hana::get<DirectionTypes>(operand.directions), old_reference)...};
	}
	auto constexpr change_reference_frame(simple_rotation_t<auto,auto,auto> const& operand, linear_map_t<auto> const& old_reference){
		return simple_rotation_t{change_reference_frame(operand.plane, old_reference), operand.angle};
	}
	auto constexpr change_reference_frame(rotation_t<auto> const& operand, linear_map_t<auto> const& old_reference){
		return rotation_t{change_reference_frame(operand.rotor(), old_reference)};
	}
	template<class Name>
	auto constexpr change_reference_frame(transformed_point_t<Name,translation_t<auto>> const& operand, linear_map_t<auto> const& old_reference){
		return transformed_point_t{operand.origin, change_reference_frame(operand.transform, old_reference)};
	}

	auto constexpr apply(VectorRotation const& transform, linear_map_t<auto> const& operand){
		return linear_map_t{hana::to_map(hana::zip_with(hana::make_pair
			,hana::keys(operand.vectors)
			,hana::values(operand.vectors)|hana::transform_with(transform)
		))};
	}
}

#endif /* GODEFV_MATH_GEOMETRY_OBJECT_FRAME_H */
