#ifndef ALGEBRA_GEOMETRIC_H
#define ALGEBRA_GEOMETRIC_H 

#include"../group/geometric.h"
#include"../group/ordering.h"
#include"../vector/addition.h"
#include"../symbolic/trigonometry.h"
#include"../symbolic/rational.h"
#include"../inverse.h"
#include"multiplication.h"

#include<boost/hana.hpp>
#include<cmath>

namespace algebra::geometric{
	using vector::zero;
	static auto constexpr one=vector::unit_t<group::geometric::one_t>{};

	//wedge operation
	struct group_wedge_operation_t{
		group::geometric::Blade{Blade2}
		static auto constexpr apply(group::geometric::Blade a, Blade2 b){
			if constexpr(grade(group::geometric::mult_operation_t::apply(a,b))==grade(a)+grade(b)){
				return group::geometric::mult_operation_t::apply(a,b);
			}else{
				return zero;
			}
		}
		static auto constexpr apply(auto const& a, auto const& b){return a*b;}
	};
	//dot operation
	struct group_dot_operation_t{
		group::geometric::Blade{Blade2}
		static auto constexpr apply(group::geometric::Blade a, Blade2 b){
			if constexpr(grade(group::geometric::mult_operation_t::apply(a,b))==std::abs(grade(a)-grade(b))){
				return group::geometric::mult_operation_t::apply(a,b);
			}else{
				return zero;
			}
		}
		static auto constexpr apply(auto const& a, auto const& b){return a*b;}
	};

	struct group_mult_operation_t{
		static auto constexpr apply(auto const& a, auto const& b){return a*b;}
		static auto constexpr inverse(auto const& a){using ::inverse; return inverse(a);}
	};

	using   add_operation_t= vector::add_operation_t;
	using  mult_operation_t=algebra::mult_operation_t<group_mult_operation_t>;
	using wedge_operation_t=algebra::mult_operation_t<group_wedge_operation_t>;
	using   dot_operation_t=algebra::mult_operation_t<group_dot_operation_t>;

	namespace hana=boost::hana;
	using namespace hana::literals;

	template<int... Is>
	auto constexpr grades(){return hana::make_set(hana::llong_c<Is>...);}
	auto constexpr grades(group::identity_t<add_operation_t> const&){return grades<>();}
	auto constexpr grades(vector::basis_element_t<auto,auto> const& a){return grades<grade(a.element)>();}
	auto constexpr grades(group::generated_by_operation_t<add_operation_t, auto,auto> const& a){
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
	auto constexpr project(group::generated_by_operation_t<add_operation_t, auto,auto> const& a, auto grades){
		return std::decay_t<decltype(a.operation)>::apply(project(a.first, grades), project(a.second, grades));
	}

	namespace operators{
		constexpr auto operator*(auto const& a, auto const& b){
			return mult_operation_t::apply(a,b);
		}
		constexpr auto operator/(auto const& a, auto const& b){
			return a*mult_operation_t::inverse(b);
		}
		constexpr auto operator-(auto const& a){
			return add_operation_t::inverse(a);
		}
		constexpr auto operator-(auto const& a, auto const& b){
			return a+(-b);
		}
		constexpr auto operator^(auto const& a, auto const& b){
			return wedge_operation_t::apply(a,b);
		}
		constexpr auto operator|(auto const& a, auto const& b){
			return dot_operation_t::apply(a,b);
		}
	}

	auto constexpr norm(auto const& a){
		using namespace operators;
		vector::basis_element_t<group::geometric::one_t, auto> a_square=(a|a);
		using std::sqrt;
		using std::abs;
		return sqrt(abs(a_square.coordinate));
	}

	auto constexpr normalized(auto const& a){
		using namespace operators;
		return a/vector::scalar_wrapper_t{norm(a)};
	}

	template<class BivectorT> 
		requires boost::hana::value(grades(BivectorT{})==grades<2>()) 
		      && symbolic::Angle<decltype(BivectorT{}.coordinate)> 
		      && symbolic::Ratio<decltype(BivectorT{}.coordinate.coordinate)> 
		      && std::is_same<decltype(BivectorT{}*BivectorT{}),vector::zero_t>::value 
	constexpr auto exp(BivectorT const& a){
			return one+a;
	}

	template<class BivectorT> 
		requires boost::hana::value(grades(BivectorT{})==grades<2>()) 
		      && symbolic::Angle<decltype(BivectorT{}.coordinate)> 
		      && symbolic::Ratio<decltype(BivectorT{}.coordinate.coordinate)> 
		      && !std::is_same<decltype(BivectorT{}*BivectorT{}),vector::zero_t>::value
			  && eval((BivectorT{}*BivectorT{}).coordinate)>0
	constexpr auto exp(BivectorT const& a){
		using namespace operators;
		vector::basis_element_t<group::geometric::one_t, auto> square=a*a;
		using std::sqrt;
		using std::abs;
		auto angle=sqrt(abs(square.coordinate));
		using std::cosh;
		using std::sinh;
		return vector::scalar_wrapper_t{vector::unit(cosh(angle))}*one
		      +vector::scalar_wrapper_t{vector::unit(sinh(angle))}*(a/vector::scalar_wrapper_t{angle});
	}

	template<class BivectorT> 
		requires boost::hana::value(grades(BivectorT{})==grades<2>()) 
		      && symbolic::Angle<decltype(BivectorT{}.coordinate)> 
		      && symbolic::Ratio<decltype(BivectorT{}.coordinate.coordinate)> 
		      && !std::is_same<decltype(BivectorT{}*BivectorT{}),vector::zero_t>::value
			  && eval((BivectorT{}*BivectorT{}).coordinate)<0
	constexpr auto exp(BivectorT const& a){
		using namespace operators;
		vector::basis_element_t<group::geometric::one_t, auto> square=a*a;
		using std::sqrt;
		using std::abs;
		auto angle=sqrt(abs(square.coordinate));
		using std::cos;
		using std::sin;
		return vector::scalar_wrapper_t{vector::unit(cos(angle))}*one
		      +vector::scalar_wrapper_t{vector::unit(sin(angle))}*(a/vector::scalar_wrapper_t{angle});
	}
}

#endif /* ALGEBRA_GEOMETRIC_H */
