#ifndef GEOMETRY_COMPOSITION_H
#define GEOMETRY_COMPOSITION_H 

#include"vector_transform.h"
#include"translation.h"

#include<iostream>

namespace math::geometry{
	struct compose_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){
			return a,b;
		}
	};
	//identity
	struct identity_t:group::identity_t<compose_operation_t>{
		auto constexpr operator()(auto const& operand) const{
			return operand;
		}
	};
	auto constexpr identity=identity_t{};
	//generated
	template<class A, class B>
	struct generated_by_composition_t:group::generated_by_operation_t<compose_operation_t,A,B>{
		generated_by_composition_t(A const& a, B const& b):group::generated_by_operation_t<compose_operation_t,A,B>{compose_operation_t{},a,b}{}
		auto constexpr operator()(auto const& operand) const{
			return this->second(this->first(operand));
		}
	};
}
namespace math{
	auto constexpr identity(geometry::compose_operation_t){return geometry::identity;}
}
namespace math::group{
	template<class A,class B> 
	struct is_generated_by_operation<geometry::compose_operation_t, geometry::generated_by_composition_t<A,B>>:std::true_type{};

	template<class A,class B> 
		requires !group::Generated<geometry::compose_operation_t,A>
		      && !group::Generated<geometry::compose_operation_t,B>
	auto constexpr operation(geometry::compose_operation_t, A const& a, B const& b){
		return geometry::generated_by_composition_t{a,b};
	}
	template<class A,class B,class C> 
		requires std::is_base_of<generated_by_operation_t<geometry::compose_operation_t,B,C>, decltype(geometry::compose_operation_t::apply(B{},C{}))>::value 
		      && !group::Generated<geometry::compose_operation_t,C>
	auto constexpr operation(geometry::compose_operation_t, geometry::generated_by_composition_t<A,B> const& ab, C const& c){
		return geometry::generated_by_composition_t{ab,c};
	}
}
namespace math::geometry{
	//concepts
	template<class T> concept bool Transform=Rotation<T> || Scaling<T> || Translation<T> || group::Generated<compose_operation_t,T>;

	//composition - group rules
	Transform{Transform2}
	auto constexpr operator,(Transform const& a, Transform2 const& b){
		return group::operation(compose_operation_t{},a,b);
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
	//composition - scalings
	Scaling{Scaling2}
	auto constexpr operator,(Scaling const& a, Scaling2 const& b){
		return scaling_t{a.factor*b.factor};
	}
	
   	//composition - put scalings first and translations last
   	auto constexpr operator,(Rotation const& a, Scaling const& b){
   		return b,a;
   	}
   	auto constexpr operator,(Translation const& a, VectorTransform const& b){
   		return geometry::operator,(b,b(a));
   	}
	
	//formatting
	inline std::ostream& operator<<(std::ostream& out, identity_t){
		return out<<"identity";
	}

	std::ostream& operator<<(std::ostream& out, generated_by_composition_t<auto,auto> const& ab){
		return out<<ab.first<<" then "<<ab.second;
	}
}

#endif /* GEOMETRY_COMPOSITION_H */
