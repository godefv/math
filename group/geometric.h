#ifndef MATHS_GROUP_GEOMETRIC_H
#define MATHS_GROUP_GEOMETRIC_H 

#include"operation.h"
#include"../geometry/direction.h"

#include<boost/hana.hpp>

#include<type_traits>

namespace group::geometric{
	//basis vectors
	template<unsigned short i> struct direction_positive_t:geometry::direction_t<i>{};
	template<unsigned short i> struct direction_negative_t:geometry::direction_t<-i>{};

	template<class> struct is_direction_t: std::false_type{};
	template<unsigned short i> struct is_direction_t<direction_positive_t<i>>: std::true_type{};
	template<unsigned short i> struct is_direction_t<direction_negative_t<i>>: std::true_type{};
	template<class A> concept bool BasisVector=is_direction_t<A>::value;

	//mult 
	template<class A,class B> 
	constexpr auto mult(A const& a, B const& b);
	struct mult_operation_t{
		template<class A,class B> 
		static auto apply(A const& a, B const& b){return mult(a,b);};

		template<class A>
		static auto inverse(A const& a){return group::inverse<mult_operation_t>(a);}

		//group order of basis vectors
		template<unsigned short i> static auto inverse(direction_positive_t<i> const& a){return a;}
		template<unsigned short i> static auto inverse(direction_negative_t<i> const& a){return group::minus<mult_operation_t>(a);}
	};
	template<class A> using inverse_t=group::inverse_t<mult_operation_t, A>;
	template<class A> using minus_t  =group::minus_t  <mult_operation_t, A>;
	using one_t=group::identity_t<mult_operation_t>;
	//commutations rules
	template<class A,class B> 
		requires !std::is_same<A,B>::value 
			&& BasisVector<A>
			&& BasisVector<B>
			&& !is_sorted(A{},B{})
	constexpr auto mult(A const& a, B const& b){
			return minus_t<decltype(mult(b,a))>{};
	}
	template<class A,class B> 
	constexpr auto mult(A const& a, B const& b){
		return group::operation<mult_operation_t>(a,b);
	}
	template<class A, class B> using mult_t=decltype(mult(A{}, B{}));
	//mult functions
	namespace hana=boost::hana;
	constexpr auto hana_mult   =[](auto const& a, auto const& b){return hana::type_c<mult_t<typename std::decay_t<decltype(a)>::type, typename std::decay_t<decltype(b)>::type>>;};
	constexpr auto hana_inverse=[](auto const& a){return hana::type_c<inverse_t<typename std::decay_t<decltype(a)>::type>>;};

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
}

#endif /* MATHS_GROUP_GEOMETRIC_H */
