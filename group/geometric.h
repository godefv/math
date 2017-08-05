#ifndef MATHS_GROUP_GEOMETRIC_H
#define MATHS_GROUP_GEOMETRIC_H 

#include"operation.h"
#include"commutation.h"

#include<boost/hana.hpp>

#include<type_traits>

namespace group::geometric{
	//basis vectors
	template<unsigned short i> struct direction_positive_t:indexed_element_t<i>{};
	template<unsigned short i> struct direction_negative_t:indexed_element_t<-i>{};

	template<class> struct is_direction_t: std::false_type{};
	template<unsigned short i> struct is_direction_t<direction_positive_t<i>>: std::true_type{};
	template<unsigned short i> struct is_direction_t<direction_negative_t<i>>: std::true_type{};
	template<class A> concept bool BasisVector=is_direction_t<A>::value;

	BasisVector{BasisVector2}
	constexpr int static_compare(BasisVector const& a, BasisVector2 const& b){return index(b)-index(a);}

	//mult 
	template<class A,class B> 
	constexpr auto mult(A const& a, B const& b);
	struct mult_operation_t{
		//commutations rules
		template<class A,class B> 
			requires !std::is_same<A,B>::value 
			      && BasisVector<A>
			      && BasisVector<B>
			      && static_compare(A{},B{})<0
		static constexpr auto apply(A const& a, B const& b){
			return group::minus<mult_operation_t>(apply(b,a));
		}
		//group order of basis vectors
		template<unsigned short i> 
		static constexpr auto apply(direction_negative_t<i> const& a, direction_negative_t<i> const& b){
			return group::minus<mult_operation_t>(group::identity_t<mult_operation_t>{});
		};
		//group rules
		template<class A,class B> 
		static constexpr auto apply(A const& a, B const& b){
			return group::operation<mult_operation_t>(a,b);
		}

		//group inverse
		template<class A>
		static constexpr auto inverse(A const& a){return group::inverse<mult_operation_t>(a);}
		//group order of basis vectors
		template<unsigned short i> static constexpr auto inverse(direction_positive_t<i> const& a){return a;}
		template<unsigned short i> static constexpr auto inverse(direction_negative_t<i> const& a){return group::minus<mult_operation_t>(a);}
	};

	using one_t=group::identity_t<mult_operation_t>;
	template<class A> using inverse_t=group::inverse_t<mult_operation_t, A>;
	template<class A> using minus_t  =group::minus_t  <mult_operation_t, A>;
	template<class A, class B> using mult_t=decltype(mult_operation_t::apply(A{}, B{}));

	static constexpr auto one=group::geometric::one_t{};

	namespace operators{
		constexpr auto operator*(auto const& a, auto const& b){
			return mult_operation_t::apply(a,b);
		}
		constexpr auto operator-(auto const& a){
			return group::minus<mult_operation_t>(a);
		}
		constexpr auto inverse(auto const& a){
			return mult_operation_t::inverse(a);
		}
	}

	//grade
	auto constexpr grade(group::identity_t<mult_operation_t> const& a){return 0;}
	auto constexpr grade(group::generated_element_t<mult_operation_t, auto,auto> const& a){
		return grade(a.first)+grade(a.second);
	}
	auto constexpr grade(group::generated_minus_t<mult_operation_t, auto> const& a){
		return grade(a.value);
	}
	auto constexpr grade(auto const& a){return 1;}

	//mult functions
	namespace hana=boost::hana;
	constexpr auto hana_mult   =[](auto const& a, auto const& b){return hana::type_c<mult_t<typename std::decay_t<decltype(a)>::type, typename std::decay_t<decltype(b)>::type>>;};
	constexpr auto hana_inverse=[](auto const& a){return hana::type_c<inverse_t<typename std::decay_t<decltype(a)>::type>>;};

	//formatting
	std::ostream& operator<<(std::ostream& out, group::generated_element_t<mult_operation_t, auto, auto> const& ab){
		return out<<"("<<ab.first<<") * ("<<ab.second<<")";
	}
	template<unsigned short i> 
	std::ostream& operator<<(std::ostream& out, direction_positive_t<i> const&){
		return out<<"p"<<i;
	}
	template<unsigned short i> 
	std::ostream& operator<<(std::ostream& out, direction_negative_t<i> const&){
		return out<<"n"<<i;
	}
	std::ostream& operator<<(std::ostream& out, one_t const&){
		return out<<"one";
	}
}

#endif /* MATHS_GROUP_GEOMETRIC_H */
