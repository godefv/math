#ifndef GEOMETRY_COMPOSITION_H
#define GEOMETRY_COMPOSITION_H 

#include"transform.h"

#include<iostream>

namespace math::geometry{
	struct compose_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a,b;
		}
	};
	//identity
	struct identity_t:group::identity_t<compose_operation_t>{
		auto constexpr operator()(auto const& a) const{
			return a;
		}
	};
	auto constexpr identity=identity_t{};
}
namespace math{
	auto constexpr identity(geometry::compose_operation_t){return geometry::identity;}
}
namespace math::geometry{
	//concepts
	template<class T> concept bool Transform=Rotation<T> || Homothecy<T> || Translation<T> || group::Generated<compose_operation_t,T>;

	//composition - group rules
	Transform{Transform2}
	auto constexpr operator,(Transform const& a, Transform2 const& b){
		return group::operation<compose_operation_t>(a,b);
	}

	//composition - rotations
	Rotation{Rotation2}
	auto constexpr operator,(Rotation const& a, Rotation2 const& b){
		auto ab_rotor=b.rotor()*a.rotor();
		//auto bivector_part=project(ab_rotor, grades<2>());
		//if constexpr(grades(ab_rotor)==grades<0,2>() && group::geometric::Blade<decltype(bivector_part)>){
			//return simple_rotation_t{};
		//}else{
		if constexpr(grades(ab_rotor)==grades<0>()){
			return identity;
		}else{
			return rotation_t{ab_rotor};
		}
		//}
	}

	//composition - translations
	Translation{Translation2}
	auto constexpr operator,(Translation const& a, Translation2 const& b){
		return translation_t{a.vector+b.vector};
	}
	
	//composition - homothecies
	Homothecy{Homothecy2}
	auto constexpr operator,(Homothecy const& a, Homothecy2 const& b){
		return homothecy_t{a.ratio*b.ratio};
	}
	
   	//composition - put homothecies first
   	auto constexpr operator,(Rotation const& a, Homothecy const& b){
   		return b,a;
   	}
   	auto constexpr operator,(Translation const& a, Homothecy const& b){
   		return b,b(a);
   	}
	
   	//composition - put translations after rotations
   	auto constexpr operator,(Translation const& a, Rotation const& b){
   		return b,b(a);
   	}
	
	//formatting
	inline std::ostream& operator<<(std::ostream& out, identity_t){
		return out<<"identity";
	}

	std::ostream& operator<<(std::ostream& out, group::generated_by_operation_t<compose_operation_t,auto,auto> const& ab){
		return out<<ab.first<<" then "<<ab.second;
	}

	//apply
	auto constexpr apply(generated_by_composition_t<auto,auto> const& ab, KVector<1> const& operand){
		return ab.second(ab.first(operand));
	}
}

#endif /* GEOMETRY_COMPOSITION_H */
