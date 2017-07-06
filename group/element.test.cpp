#include"group.h"

#include<boost/hana.hpp>

#include<type_traits>
#include<typeinfo>
#include<iostream>

struct e1_t{};
struct e2_t{};
struct e3_t{};
constexpr auto orthogonal_basis=hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>, hana::type_c<e3_t>);

template<class A, class B> struct mult_impl_t: group::operation_t<::mult_impl_t,A,B>{};
template<class A, class B> using mult_t=typename mult_impl_t<A,B>::type;
template<class A> using mult_inverse_t=group::inverse_t<mult_impl_t, A>;
using one_t=group::identity_t<mult_impl_t>;

template<class A, class B> struct add_impl_t: group::operation_t<::add_impl_t,A,B>{};
template<class A, class B> using add_t=typename add_impl_t<A,B>::type;
template<class A> using add_inverse_t=group::inverse_t<add_impl_t, A>;
using zero_t=group::identity_t<add_impl_t>;

template<class A> struct generated_minus_t{};
template<class A> struct minus_impl_t{using type=generated_minus_t<A>;};
template<class A> struct minus_impl_t<generated_minus_t<A>>{using type=A;};
template<class A> using minus_t=typename minus_impl_t<A>::type;

//mult rules
namespace group{
template<> struct inverse_impl_t<mult_impl_t, e1_t>{using type=e1_t;}; 
template<> struct inverse_impl_t<mult_impl_t, e2_t>{using type=e2_t;}; 
}
template<> struct mult_impl_t<e2_t,e1_t>{using type=minus_t<mult_t<e1_t,e2_t>>;};
template<class A, class B> struct mult_impl_t<A,generated_minus_t<B>>{using type=minus_t<mult_t<A,B>>;};
template<class A, class B> struct mult_impl_t<generated_minus_t<A>,B>{using type=minus_t<mult_t<A,B>>;};
template<class A, class B> struct mult_impl_t<generated_minus_t<A>,generated_minus_t<B>>{using type=mult_t<A,B>;};
namespace group{
template<> struct inverse_impl_t<mult_impl_t, mult_t<e2_t,e1_t>>: mult_impl_t<e1_t,e2_t>{};
template<> struct inverse_impl_t<mult_impl_t, mult_t<e1_t,e2_t>>: mult_impl_t<e2_t,e1_t>{};
template<class A> struct inverse_impl_t<mult_impl_t, generated_minus_t<A>>: minus_impl_t<mult_inverse_t<A>>{};
}

template<class T> void check_mult_group_element(T*)
requires group::AbsorbsIdentityElement<T, one_t, mult_t> 
      && group::HasInverse            <T, one_t, mult_t, mult_inverse_t> 
{}

//add rules
namespace group{
template<class A> requires !std::is_same<A,zero_t>::value 
struct inverse_impl_t<add_impl_t, A>{using type=minus_t<A>;}; 
}
//template<class A, class B> concept bool OrderedTypes=&typeid(A)<&typeid(B);
//OrderedTypes{A,B} struct add_impl_t<B,A>{using type=add_t<A,B>;};

template<class T> void check_add_group_element(T*)
requires group::AbsorbsIdentityElement<T, zero_t, add_t> 
      && group::HasInverse            <T, zero_t, add_t, add_inverse_t> 
{}

int main(){
	using namespace group;

	//inverse
	static_assert(std::is_same<e1_t
                              ,mult_inverse_t<mult_inverse_t<e1_t>> 
                              >::value);
	//identity
	static_assert(std::is_same<identity_t<mult_impl_t>
                              ,mult_inverse_t<identity_t<mult_impl_t>> 
                              >::value);
	static_assert(std::is_same<mult_t<one_t,e1_t>
                              ,e1_t 
                              >::value);
	static_assert(std::is_same<e1_t
                              ,mult_t<identity_t<mult_impl_t>,e1_t>
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

	check_mult_group_element((e1_t*)nullptr);
	check_mult_group_element((mult_t<e1_t, e2_t>*)nullptr);

	check_add_group_element((e1_t*)nullptr);
	check_add_group_element((mult_t<e1_t, e2_t>*)nullptr);

	auto mult   =[](auto const& a, auto const& b){return hana::type_c<mult_t<typename std::decay_t<decltype(a)>::type, typename std::decay_t<decltype(b)>::type>>;};
	auto add    =[](auto const& a, auto const& b){return hana::type_c<add_t <typename std::decay_t<decltype(a)>::type, typename std::decay_t<decltype(b)>::type>>;};
	auto inverse=[](auto const& a){return hana::type_c<mult_inverse_t<typename std::decay_t<decltype(a)>::type>>;};

	auto geometric_group_2d=generate_group(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>), inverse, mult);
	std::cout<<"geometric_group_2d"<<std::endl;
	hana::for_each(geometric_group_2d, [](auto const& element){
		std::cout<<typeid(element).name()<<std::endl;
	});

	auto complex_group=generate_group(hana::make_set(hana::type_c<mult_t<e1_t,e2_t>>), inverse, mult);
	std::cout<<"complex_group"<<std::endl;
	hana::for_each(complex_group, [](auto const& element){
		std::cout<<typeid(element).name()<<std::endl;
	});

	std::cout<<"algebra"<<std::endl;
	hana::for_each(add_procucts(complex_group, add), [](auto const& element){
		std::cout<<typeid(element).name()<<std::endl;
	});

	return 0;
}

