#include"generate.h"
#include"minus.h"
#include"geometric.h"
#include"concept.h"
#include"../sorted.h"
#include"../unit_test.h"

#include<boost/hana.hpp>

#include<type_traits>
#include<typeinfo>
#include<iostream>

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_positive_t<3>;
using namespace group::geometric;

#define DEBUG_MULT_OPERATION 0
void test_mult_operations(){
	//inverse
	static_assert(std::is_same<e1_t
                              ,inverse_t<inverse_t<e1_t>> 
                              >::value);
	static_assert(std::is_same<e1_t
                              ,inverse_t<e1_t> 
                              >::value);
	static_assert(std::is_same<inverse_t<e1_t>
                              ,decltype(mult_operation_t::inverse(e1_t{}))
                              >::value);
	static_assert(std::is_same<inverse_t<mult_t<e1_t,e2_t>>
							  ,mult_t<inverse_t<e2_t>, inverse_t<e1_t>>
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
	//minus
	static_assert(std::is_same<inverse_t<minus_t<e1_t>>
                              ,minus_t<inverse_t<e1_t>>
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
	static_assert(std::is_same<mult_t<e1_t,e2_t>
	                    	  ,minus_t<mult_t<e2_t,e1_t>>
	                    	  >::value);
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

#if !DEBUG_MULT_OPERATION
//mult groups, finite order of generators plus commutation rules guarantees that the group is finite
constexpr auto geometric_group_2d=group::generate(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>), hana_inverse, hana_mult);
constexpr auto complex_group=group::generate(hana::make_set(hana::type_c<mult_t<e1_t,e2_t>>), hana_inverse, hana_mult);
constexpr auto geometric_group_3d=group::generate(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>, hana::type_c<e3_t>), hana_inverse, hana_mult);

template<class GroupT, class T> void check_mult_group_element(T*)
	requires group::GroupElement<GroupT, T, one_t, mult_operation_t, inverse_t> 
{}

template<class T> void check_geometric_group(T const&)
requires group::Group<T, one_t, mult_operation_t, inverse_t> 
{}
#endif

int main(){
	test_mult_operations();

#if !DEBUG_MULT_OPERATION
	check_mult_group_element<decltype(geometric_group_2d)>((e1_t*)nullptr);
	check_mult_group_element<decltype(geometric_group_2d)>((mult_t<e1_t, e2_t>*)nullptr);

	check_geometric_group(geometric_group_2d);
	check_geometric_group(complex_group);
	check_geometric_group(geometric_group_3d);

	std::cout<<"geometric_group_2d"<<std::endl;
	hana::for_each(geometric_group_2d, [](auto const& element){
		print_type(element);
	});

	std::cout<<"complex_group"<<std::endl;
	hana::for_each(complex_group, [](auto const& element){
		print_type(element);
	});

	std::cout<<"geometric_group_3d"<<std::endl;
	hana::for_each(geometric_group_3d, [](auto const& element){
		print_type(element);
	});
#endif

	return 0;
}

