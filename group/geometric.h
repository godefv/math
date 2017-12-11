#ifndef MATHS_GROUP_GEOMETRIC_H
#define MATHS_GROUP_GEOMETRIC_H 

#include"operation.h"
#include"commutation.h"

#include<boost/hana.hpp>

#include<type_traits>

namespace group::geometric{
	//directions definition
	template<unsigned short i> struct direction_positive_t:indexed_element_t<i>{};
	template<unsigned short i> struct direction_negative_t:indexed_element_t<-i>{};

	//direction concept
	template<class> struct is_direction_t: std::false_type{};
	template<unsigned short i> struct is_direction_t<direction_positive_t<i>>: std::true_type{};
	template<unsigned short i> struct is_direction_t<direction_negative_t<i>>: std::true_type{};
	template<class A> concept bool Direction=is_direction_t<A>::value;

	//blade concept
	struct mult_operation_t;
	template<class T> concept bool Blade=Direction<T> 
	                                  || std::is_same<T, identity_t<mult_operation_t>>::value
	                                  || Minus<mult_operation_t, T>
	                                  || Generated<mult_operation_t, T>
	                                  ;

	//ordering for commutation
	Direction{Direction2}
	constexpr int static_compare(Direction const& a, Direction2 const& b){return index(b)-index(a);}

	//mult operation
	struct mult_operation_t{
		//commutations rules
		template<class A,class B> 
			requires Direction<A>
			      && Direction<B>
			      && static_compare(A{},B{})<0
		static constexpr auto apply(A const& a, B const& b){
			return group::minus<mult_operation_t>(apply(b,a));
		}
		//group order of basis vectors
		template<unsigned short i> 
		static constexpr auto apply(direction_negative_t<i> const&, direction_negative_t<i> const&){
			return group::minus<mult_operation_t>(group::identity_t<mult_operation_t>{});
		};
		//note: square of positive directions is identity, which falls under x*inverse(x)=1
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

	//grade
	auto constexpr grade(auto const&){return 0;}
	auto constexpr grade(Direction const&){return 1;}
	auto constexpr grade(group::identity_t<mult_operation_t> const&){return 0;}
	auto constexpr grade(group::generated_element_t<mult_operation_t, auto,auto> const& a){
		return grade(a.first)+grade(a.second);
	}
	auto constexpr grade(group::generated_minus_t<mult_operation_t, auto> const& a){
		return grade(a.value);
	}

	//operators
	Blade{Blade2}
	constexpr auto operator*(Blade const& a, Blade2 const& b){
		return mult_operation_t::apply(a,b);
	}
	constexpr auto operator-(Blade const& a){
		return group::minus<mult_operation_t>(a);
	}
	constexpr auto inverse(Blade const& a){
		return mult_operation_t::inverse(a);
	}

	//contstexpr aliases
	using one_t=group::identity_t<mult_operation_t>;
	template<class A> using inverse_t=group::inverse_t<mult_operation_t, A>;
	template<class A> using minus_t  =group::minus_t  <mult_operation_t, A>;
	template<class A, class B> using mult_t=decltype(mult_operation_t::apply(A{}, B{}));

	static constexpr auto one=group::geometric::one_t{};

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
	inline std::ostream& operator<<(std::ostream& out, one_t const&){
		return out<<"one";
	}
	//for debug only, should never be used
	//std::ostream& operator<<(std::ostream& out, group::generated_inverse_t<mult_operation_t, auto> const& a){
		//return out<<"("<<a.value_before_inverse<<")⁻¹";
	//}
}

#endif /* MATHS_GROUP_GEOMETRIC_H */
