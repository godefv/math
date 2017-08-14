#ifndef ALGEBRA_GEOMETRIC_H
#define ALGEBRA_GEOMETRIC_H 

#include"../group/geometric.h"
#include"../group/ordering.h"
#include"../vector/addition.h"
#include"multiplication.h"

#include<boost/hana.hpp>
#include<cmath>

namespace algebra::geometric{
	using  add_operation_t=vector:: add_operation_t;
	vector::Scalar{ScalarT} using mult_operation_t=algebra::mult_operation_t<group::geometric::mult_operation_t, ScalarT>;

	auto constexpr zero=group::identity_t<add_operation_t>{};

	namespace hana=boost::hana;
	using namespace hana::literals;

	template<int... Is>
	auto constexpr grades(){return hana::make_set(hana::llong_c<Is>...);}
	auto constexpr grades(group::identity_t<add_operation_t> const&){return grades<>();}
	auto constexpr grades(vector::basis_element_t<auto,auto> const& a){return grades<grade(a.element)>();}
	auto constexpr grades(group::generated_element_t<add_operation_t, auto,auto> const& a){
		return hana::union_(grades(a.first), grades(a.second));
	}

	auto constexpr project(group::identity_t<add_operation_t> const& a, auto const& grades){return zero;}
	auto constexpr project(vector::basis_element_t<auto,auto> const& a, auto grades){
		if constexpr(hana::find(grades, hana::llong_c<grade(a.element)>)==hana::nothing){
			return zero;
		}else{
			return a;
		}
	}
	auto constexpr project(group::generated_element_t<add_operation_t, auto,auto> const& a, auto grades){
		return std::decay_t<decltype(a.operation)>::apply(project(a.first, grades), project(a.second, grades));
	}

	struct group_wedge_operation_t{
		static auto constexpr apply(auto a, auto b){
			if constexpr(grade(group::geometric::mult_operation_t::apply(a,b))==grade(a)+grade(b)){
				return group::geometric::mult_operation_t::apply(a,b);
			}else{
				return zero;
			}
		}
	};

	struct group_dot_operation_t{
		static auto constexpr apply(auto a, auto b){
			if constexpr(grade(group::geometric::mult_operation_t::apply(a,b))==std::abs(grade(a)-grade(b))){
				return group::geometric::mult_operation_t::apply(a,b);
			}else{
				return zero;
			}
		}
	};

	vector::Scalar{ScalarT} using wedge_operation_t=algebra::mult_operation_t<group_wedge_operation_t, ScalarT>;
	vector::Scalar{ScalarT} using   dot_operation_t=algebra::mult_operation_t<  group_dot_operation_t, ScalarT>;

	namespace operators{
		constexpr auto operator*(auto const& a, auto const& b){
			return mult_operation_t<double>::apply(a,b);
		}
		constexpr auto operator/(auto const& a, auto const& b){
			return a*mult_operation_t<double>::inverse(b);
		}
		constexpr auto operator+(auto const& a, auto const& b){
			return add_operation_t::apply(a,b);
		}
		constexpr auto operator-(auto const& a){
			return add_operation_t::inverse(a);
		}
		constexpr auto operator-(auto const& a, auto const& b){
			return a+(-b);
		}
		constexpr auto operator^(auto const& a, auto const& b){
			return wedge_operation_t<double>::apply(a,b);
		}
		constexpr auto operator|(auto const& a, auto const& b){
			return dot_operation_t<double>::apply(a,b);
		}
	}

	auto constexpr norm(auto const& a){
		using namespace operators;
		vector::basis_element_t<group::identity_t<group::geometric::mult_operation_t>, auto> a_square=(a|a);
		return std::sqrt(std::abs(a_square.coordinate));
	}

	auto constexpr normalized(auto const& a){
		using namespace operators;
		return a/norm(a);
	}
}
#endif /* ALGEBRA_GEOMETRIC_H */
