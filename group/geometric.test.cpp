#include"generate.h"
#include"minus.h"
#include"geometric.h"
#include"concept.h"
#include"../unit_test.h"

#include<boost/hana.hpp>

#include<type_traits>
#include<typeinfo>
#include<iostream>

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_negative_t<3>;
static constexpr auto e1=e1_t{};
static constexpr auto e2=e2_t{};
static constexpr auto e3=e3_t{};
using namespace group::geometric::operators;
using group::geometric::one;

#define DEBUG_MULT_OPERATION 0
void test_mult_operations(){
	//inverse of inverse
	check_equal(inverse(inverse(e1)), e1);
	check_equal(inverse(inverse(e3)), e3);
	//inverse of generators
	check_equal(inverse(e1),  e1);
	check_equal(inverse(e3), -e3);
	check_equal(inverse(e1*e2), inverse(e2)*inverse(e1));
	//identity
	check_equal(one, inverse(one));
	check_equal(one*e1, e1);
	check_equal(e1*one, e1);
	//minus
	check_equal(inverse(-e1), -inverse(e1));
	//associativity 
	check_equal(e2*(e1*e2), (e2*e1)*e2);
	//1(12)
	check_equal(e1*(e1*e2), e2);
	//(12)2
	check_equal((e1*e2)*e2, e1);
	//commutativity
	//21
	static_assert(static_compare(e2,e1)<0);
	check_equal(e1*e2, -(e2*e1));
	check_equal(e2*e1, -(e1*e2));
	//(12)1
	check_equal((e1*e2)*e1, -(e1*(e1*e2)));
	check_equal((e1*e2)*e1, -e2);
	//(21)1
	check_equal((e2*e1)*e1, -((e1*e2)*e1));
	check_equal((e2*e1)*e1, e2);
	//(12)(12)
	check_equal((e1*e2)*(e1*e2), ((e1*e2)*e1)*e2);
	check_equal((e1*e2)*(e1*e2), -one);
	//(21)(21)
	check_equal((e2*e1)*(e2*e1), -one);
	//(21)(12)
	check_equal((e2*e1)*(e1*e2), ((e2*e1)*e1)*e2);
	check_equal((e2*e1)*(e1*e2), one);
}

#if !DEBUG_MULT_OPERATION
using namespace group::geometric;
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
		std::cout<<typename std::decay_t<decltype(element)>::type{}<<std::endl;
	});

	std::cout<<"complex_group"<<std::endl;
	hana::for_each(complex_group, [](auto const& element){
		std::cout<<typename std::decay_t<decltype(element)>::type{}<<std::endl;
	});

	std::cout<<"geometric_group_3d"<<std::endl;
	hana::for_each(geometric_group_3d, [](auto const& element){
		std::cout<<typename std::decay_t<decltype(element)>::type{}<<std::endl;
	});
#else
	constexpr auto geometric_group_3d=group::add_procucts(boost::hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>, hana::type_c<e3_t>), hana_mult);
	std::cout<<"geometric_group_3d"<<std::endl;
	hana::for_each(geometric_group_3d, [](auto const& element){
		std::cout<<typename std::decay_t<decltype(element)>::type{}<<std::endl;
	});
#endif

	return 0;
}

