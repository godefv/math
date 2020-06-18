#ifndef GEOMETRY_SCALING_H
#define GEOMETRY_SCALING_H 

#include"../algebra/grade.h"

#include<type_traits>
#include<iostream>

namespace godefv::math::geometry{
	//concept
	template<class T> struct is_scaling:std::false_type{};
	template<class T> concept Scaling=is_scaling<T>::value;

	//apply
	auto constexpr apply(Scaling auto const& scaling, Vector auto const& operand){
		return scaling.factor*operand;
	}

	//scaling_t
	template<class ScalarT=double>
	struct scaling_t{
		ScalarT factor;
		auto constexpr operator()(auto const& a) const{
			return apply(*this, a);
		}
	};
	template<class ScalarT>
	scaling_t(ScalarT const&)->scaling_t<ScalarT>;

	template<class ScalarT> struct is_scaling<scaling_t<ScalarT>>:std::true_type{};

	std::ostream& operator<<(std::ostream& out, scaling_t<auto> const& t){
		return out<<"scaling{"<<t.factor<<"}";
	}

	bool constexpr operator==(scaling_t<auto> const& a, scaling_t<auto> const& b){
		return a.factor==b.factor;
	}
	bool constexpr operator!=(scaling_t<auto> const& a, scaling_t<auto> const& b){
		return !(a==b);
	}
	//std::strong_equality operator<=>(scaling_t const&, scaling_t const&) = default;
}

#endif /* GEOMETRY_SCALING_H */
