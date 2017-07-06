#include"group.h"

#include<boost/hana.hpp>

#include<type_traits>
#include<typeinfo>
#include<iostream>

template<class A, class B> struct mult_impl_t: group::operation_t<::mult_impl_t,A,B>{};
template<class A, class B> using mult_t=typename mult_impl_t<A,B>::type;

struct e1_t{};
struct e2_t{};
template<class A> struct generated_minus_t{};
template<class A> struct minus_impl_t{using type=generated_minus_t<A>;};
template<class A> struct minus_impl_t<generated_minus_t<A>>{using type=A;};
template<class A> using minus_t=typename minus_impl_t<A>::type;

namespace group{
template<> struct inverse_impl_t<e1_t>{using type=e1_t;}; 
template<> struct inverse_impl_t<e2_t>{using type=e2_t;}; 
}
template<> struct mult_impl_t<e2_t,e1_t>{using type=minus_t<mult_t<e1_t,e2_t>>;};
template<class A, class B> struct mult_impl_t<A,generated_minus_t<B>>{using type=minus_t<mult_t<A,B>>;};
template<class A, class B> struct mult_impl_t<generated_minus_t<A>,B>{using type=minus_t<mult_t<A,B>>;};
template<class A, class B> struct mult_impl_t<generated_minus_t<A>,generated_minus_t<B>>{using type=mult_t<A,B>;};
namespace group{
template<> struct inverse_impl_t<mult_t<e2_t,e1_t>>: mult_impl_t<e1_t,e2_t>{};
template<> struct inverse_impl_t<mult_t<e1_t,e2_t>>: mult_impl_t<e2_t,e1_t>{};
}

template<class T> void f(T*)
requires group::AbsorbsIdentityElement<T, group::identity_t<mult_impl_t>, mult_t> 
      && group::HasInverse            <T, group::identity_t<mult_impl_t>, mult_t, group::inverse_t> 
{}

int main(){
	using namespace group;

	//inverse
	static_assert(std::is_same<e1_t
                              ,inverse_t<inverse_t<e1_t>> 
                              >::value);
	//identity
	static_assert(std::is_same<identity_t<mult_impl_t>
                              ,inverse_t<identity_t<mult_impl_t>> 
                              >::value);
	static_assert(std::is_same<mult_t<group::identity_t<mult_impl_t>,e1_t>
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
                              ,minus_t<group::identity_t<mult_impl_t>>
                              >::value);
	//(21)(21)
	static_assert(std::is_same<mult_t<mult_t<e2_t,e1_t>,mult_t<e2_t,e1_t>>
                              ,minus_t<group::identity_t<mult_impl_t>>
                              >::value);
	//(21)(12)
	static_assert(std::is_same<mult_t<mult_t<e2_t,e1_t>,mult_t<e1_t,e2_t>>
                              ,mult_t<mult_t<mult_t<e2_t,e1_t>,e1_t>,e2_t>
                              >::value);
	static_assert(std::is_same<mult_t<mult_t<e2_t,e1_t>,mult_t<e1_t,e2_t>>
                              ,group::identity_t<mult_impl_t>
                              >::value);

	f((e1_t*)nullptr);
	f((mult_t<e1_t, e2_t>*)nullptr);

	auto group=generate_group(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>)
		, [](auto const& a){return hana::type_c<inverse_t<typename std::decay_t<decltype(a)>::type>>;}
		, [](auto const& a, auto const& b){return hana::type_c<mult_t<typename std::decay_t<decltype(a)>::type, typename std::decay_t<decltype(b)>::type>>;}
	);

	hana::for_each(group, [](auto const& element){
		std::cout<<typeid(element).name()<<std::endl;
	});
	return 0;
}

