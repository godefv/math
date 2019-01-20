#ifndef GEOMETRY_COMPOSITION_H
#define GEOMETRY_COMPOSITION_H 

#include"../group/operation.h"

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
		constexpr generated_by_composition_t(A const& a, B const& b):group::generated_by_operation_t<compose_operation_t,A,B>{compose_operation_t{},a,b}{}
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
	//composition - group rules
	auto constexpr operator,(auto const& a, auto const& b){
		return group::operation(compose_operation_t{},a,b);
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
