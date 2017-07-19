#include"generate.h"
#include"minus.h"
#include"geometric.h"
#include"concept.h"
#include"../sorted.h"

#include<boost/hana.hpp>

#include<type_traits>
#include<typeinfo>
#include<iostream>

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_positive_t<3>;
using namespace group::geometric;

void test_mult_operations(){
	//inverse
	static_assert(std::is_same<e1_t
                              ,inverse_t<inverse_t<e1_t>> 
                              >::value);
	//identity
	static_assert(std::is_same<one_t
                              ,inverse_t<one_t> 
                              >::value);
	static_assert(std::is_same<mult_t<one_t,e1_t>
                              ,e1_t 
                              >::value);
	static_assert(std::is_same<e1_t
                              ,mult_t<one_t,e1_t>
                              >::value);
	//associativity 
	static_assert(std::is_same<mult_t<e2_t,mult_t<e1_t,e2_t>>
                              ,mult_t<mult_t<e2_t,e1_t>,e2_t> 
                              >::value);
	//1(12)
	static_assert(std::is_same<mult_t<e1_t,mult_t<e1_t,e2_t>>
                              ,e2_t
                              >::value);
	//(12)2
	static_assert(std::is_same<mult_t<mult_t<e1_t,e2_t>,e2_t>
                              ,e1_t
                              >::value);
	//commutativity
	//21
	static_assert(BasisVector<e2_t>     );
	static_assert(BasisVector<e1_t>     );
	static_assert(!is_sorted(e2_t{},e1_t{}));
	static_assert(std::is_same<mult_t<e2_t,e1_t>
	                    	  ,minus_t<mult_t<e1_t,e2_t>>
	                    	  >::value);
	//(12)1
	static_assert(std::is_same<mult_t<mult_t<e1_t,e2_t>,e1_t>
	                    	  ,minus_t<mult_t<e1_t,mult_t<e1_t,e2_t>>>
	                    	  >::value);
	static_assert(std::is_same<mult_t<mult_t<e1_t,e2_t>,e1_t>
	                    	  ,minus_t<e2_t>
	                    	  >::value);
	//(21)1
	static_assert(std::is_same<mult_t<mult_t<e2_t,e1_t>,e1_t>
	                    	  ,minus_t<mult_t<mult_t<e1_t,e2_t>,e1_t>>
	                    	  >::value);
	static_assert(std::is_same<mult_t<mult_t<e2_t,e1_t>,e1_t>
	                    	  ,e2_t
	                    	  >::value);
	//(12)(12)
	static_assert(std::is_same<mult_t<mult_t<e1_t,e2_t>,mult_t<e1_t,e2_t>>
	                    	  ,mult_t<mult_t<mult_t<e1_t,e2_t>,e1_t>,e2_t> 
	                    	  >::value);
	static_assert(std::is_same<mult_t<mult_t<e1_t,e2_t>,mult_t<e1_t,e2_t>>
	                    	  ,minus_t<one_t>
	                    	  >::value);
	//(21)(21)
	static_assert(std::is_same<mult_t<mult_t<e2_t,e1_t>,mult_t<e2_t,e1_t>>
	                    	  ,minus_t<one_t>
	                    	  >::value);
	//(21)(12)
	static_assert(std::is_same<mult_t<mult_t<e2_t,e1_t>,mult_t<e1_t,e2_t>>
	                    	  ,mult_t<mult_t<mult_t<e2_t,e1_t>,e1_t>,e2_t>
	                    	  >::value);
	static_assert(std::is_same<mult_t<mult_t<e2_t,e1_t>,mult_t<e1_t,e2_t>>
	                    	  ,one_t
	                    	  >::value);
}

//mult groups, finite order of generators plus commutation rules guarantees that the group is finite
constexpr auto geometric_group_2d=group::generate(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>), hana_inverse, hana_mult);
constexpr auto complex_group=group::generate(hana::make_set(hana::type_c<mult_t<e1_t,e2_t>>), hana_inverse, hana_mult);
constexpr auto geometric_group_3d=group::generate(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>, hana::type_c<e3_t>), hana_inverse, hana_mult);

//add rules
template<class A, class B> struct add_impl_t: group::operation_t<::add_impl_t,A,B>{};
template<class A, class B> using add_t=typename add_impl_t<A,B>::type;
using zero_t=group::identity_t<add_impl_t>;

namespace group{
template<class A> requires !std::is_same<A,zero_t>::value 
struct inverse_impl_t<add_impl_t, A>{using type=::minus_t<A>;}; 
}
template<class A, class B> 
	requires !std::is_same<A,B>::value 
		  && !Sorted<decltype(geometric_group_3d),A,B> 
struct add_impl_t<A,B>{using type=add_t<B,A>;};
//add functions
constexpr auto add  =[](auto const& a, auto const& b){return hana::type_c<add_t <typename std::decay_t<decltype(a)>::type, typename std::decay_t<decltype(b)>::type>>;};
constexpr auto minus=[](auto const& a){return hana::type_c<minus_t<typename std::decay_t<decltype(a)>::type>>;};

template<class T> void check_mult_group_element(T*)
requires group::AbsorbsIdentityElement<T, one_t, mult_t> 
	  && group::HasInverse            <T, one_t, mult_t, inverse_t> 
{}

template<class T> void check_add_group_element(T*)
requires group::AbsorbsIdentityElement<T, zero_t, add_t> 
	  && group::HasInverse            <T, zero_t, add_t, minus_t> 
{}

template<class T> void check_geometric_group(T const&)
requires group::Group<T, one_t, mult_t, inverse_t> 
{}

int main(){
	test_mult_operations();

	check_mult_group_element((e1_t*)nullptr);
	check_mult_group_element((mult_t<e1_t, e2_t>*)nullptr);

	check_add_group_element((e1_t*)nullptr);
	check_add_group_element((mult_t<e1_t, e2_t>*)nullptr);

	check_geometric_group(geometric_group_2d);
	check_geometric_group(complex_group);
	check_geometric_group(geometric_group_3d);

	std::cout<<"geometric_group_2d"<<std::endl;
	hana::for_each(geometric_group_2d, [](auto const& element){
		std::cout<<typeid(element).name()<<std::endl;
	});

	std::cout<<"complex_group"<<std::endl;
	hana::for_each(complex_group, [](auto const& element){
		std::cout<<typeid(element).name()<<std::endl;
	});

	std::cout<<"geometric_group_3d"<<std::endl;
	hana::for_each(geometric_group_3d, [](auto const& element){
		std::cout<<typeid(element).name()<<std::endl;
	});

	//std::cout<<"algebra"<<std::endl;
	//hana::for_each(add_procucts(complex_group, add), [](auto const& element){
		//std::cout<<typeid(element).name()<<std::endl;
	//});

	return 0;
}

