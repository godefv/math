#ifndef GODEFV_MATH_GEOMETRY_FRAME_ORIENTATION
#define GODEFV_MATH_GEOMETRY_FRAME_ORIENTATION 

#include"linear_map.h"
#include"../algebra/reference_frame.h"
#include"../object/direction.h"
#include"../vector_transform/rotation.h"
#include"../vector_transform/composition.h"
#include"../../hana.h"

#include<iostream>

namespace godefv::math::geometry{
	namespace hana=boost::hana;

	template<class DirectionsT, class ReferenceDirectionsT, VectorRotation RotationT>
	requires (static_cast<bool>(hana::size(DirectionsT{})==hana::size(ReferenceDirectionsT{}))
	&& static_cast<bool>(hana::is_subset(
		get_reference_frame(RotationT{}.rotor()), hana::to_set(ReferenceDirectionsT{})
	)))
	struct orientation_t{
		DirectionsT frame;
		ReferenceDirectionsT reference_frame;
		RotationT rotation_from_reference;
	};
	template<Direction... DirectionTs, Direction... ReferenceDirectionTs, VectorRotation RotationT>
	orientation_t(hana::tuple<DirectionTs...> const&, hana::tuple<ReferenceDirectionTs...> const&, RotationT const&)
	->orientation_t<hana::tuple<DirectionTs...>, hana::tuple<ReferenceDirectionTs...>, RotationT>;

	//operators
	template<class Directions1, class ReferenceDirections1, class Rotation1, class Directions2, class ReferenceDirections2, class Rotation2>
	auto constexpr operator==(orientation_t<Directions1,ReferenceDirections1,Rotation1> const& a, orientation_t<Directions2,ReferenceDirections2,Rotation2> const& b){
		return a.reference_frame==b.reference_frame && a.frame==b.frame && a.rotation_from_reference==b.rotation_from_reference;
	}
	template<class Directions1, class ReferenceDirections1, class Rotation1, class Directions2, class ReferenceDirections2, class Rotation2>
	auto constexpr operator!=(orientation_t<Directions1,ReferenceDirections1,Rotation1> const& a, orientation_t<Directions2,ReferenceDirections2,Rotation2> const& b){
		return !(a==b);
	}
	template<class DirectionsT, class ReferenceDirectionsT, class RotationT>
	std::ostream& operator<<(std::ostream& out, orientation_t<DirectionsT,ReferenceDirectionsT,RotationT> const& operand){
		return out<<"orientation{"<<operand.frame<<":="<<operand.rotation_from_reference<<"("<<operand.reference_frame<<")";
	}

	//apply geometric tranformations
	template<class DirectionsT, class ReferenceDirectionsT, class RotationT>
	auto constexpr apply(VectorRotation auto const& transform, orientation_t<DirectionsT,ReferenceDirectionsT,RotationT> const& operand){
		return orientation_t{operand.frame, operand.reference_frame, (operand.rotation_from_reference,transform)};
	}
	template<VectorTransform VectorTransformT, class DirectionsT, class ReferenceDirectionsT, class RotationT> requires (!VectorRotation<VectorTransformT>)
	auto constexpr apply(VectorTransformT const& transform, orientation_t<DirectionsT,ReferenceDirectionsT,RotationT> const& operand){
		return operand;
	}

	//to_linear_map
	template<class DirectionsT, class ReferenceDirectionsT, class RotationT>
	auto constexpr to_linear_map(orientation_t<DirectionsT,ReferenceDirectionsT,RotationT> const& operand){
		return linear_map_t{boost::hana::to_map(hana::zip_with(hana::make_pair
			,operand.frame
			,hana::transform(operand.reference_frame, operand.rotation_from_reference)
		))};
	}

	//inverse
	template<class DirectionsT, class ReferenceDirectionsT, class RotationT>
	auto constexpr inverse(orientation_t<DirectionsT,ReferenceDirectionsT,RotationT> const& operand){
		return orientation_t{operand.reference_frame, operand.frame, change_reference_frame(
			inverse(operand.rotation_from_reference)
			,linear_map_t{hana::to_map(hana::zip_with(hana::make_pair
				,operand.reference_frame
				,operand.frame
			))}
		)};
	}

	//change_reference_frame
	//use `change_reference_frame(operand, to_linear_map(orientation))`
	
}

#endif /* GODEFV_MATH_GEOMETRY_FRAME_ORIENTATION */
