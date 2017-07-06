#include"element.h"
#include"operation.h"
#include<type_traits>

template<class A, class B> struct mult_t: group::operation_t<::mult_t,A,B>{};
//template<class A, class B> using mult_t=typename mult_impl_t<A,B>::type;

struct e1_t{};
struct e2_t;
template<class A> struct minus_one_t;

namespace group{
template<> struct inverse_impl_t<e1_t>{using type=e1_t;}; 
template<> struct inverse_impl_t<e2_t>{using type=e2_t;}; 
}
template<> struct mult_t<e2_t,e1_t>{using type=minus_one_t<mult_t<e1_t,e2_t>::type>;};
template<class A, class B> struct mult_t<A,minus_one_t<B>>{using type=minus_one_t<typename mult_t<A,B>::type>;};
template<class A, class B> struct mult_t<minus_one_t<A>,B>{using type=minus_one_t<typename mult_t<A,B>::type>;};
template<class A, class B> struct mult_t<minus_one_t<A>,minus_one_t<B>>:mult_t<A,B>{};
namespace group{
template<> struct inverse_impl_t<mult_t<e2_t,e1_t>::type>: mult_t<e1_t,e2_t>{};
template<> struct inverse_impl_t<mult_t<e1_t,e2_t>::type>: mult_t<e2_t,e1_t>{};
}

namespace group{
template<template<class, class> class BinaryOperator>
struct operation{template<class A, class B> typename BinaryOperator<A,B>::type operator()(A,B);};
struct inverse  {template<class A> inverse_t<A> operator()(A);};
}

template<class T> void f(T*)
requires AbsorbsIdentityElementAndHasInverse<T, group::identity_t<mult_t>, group::operation<mult_t>, group::inverse> 
{}

template<class A, class B> void static_check_equal(){
	static_assert(std::is_same<A,B>::value, "static_check_equal failed");
}

int main(){
	using namespace group;

	//inverse
	static_check_equal<e1_t
	                  ,inverse_t<inverse_t<e1_t>> 
					  >();
	//identity
	static_check_equal<identity_t<mult_t>
	                  ,inverse_t<identity_t<mult_t>> 
					  >();
	static_check_equal<mult_t<group::identity_t<mult_t>,e1_t>::type
	                  ,e1_t 
					  >();
	static_check_equal<e1_t
	                  ,mult_t<identity_t<mult_t>,e1_t>::type 
					  >();
	//associativity
	static_check_equal<mult_t<e2_t,mult_t<e1_t,e2_t>::type>::type
	                  ,mult_t<mult_t<e2_t,e1_t>::type,e2_t>::type 
					  >();
	static_check_equal<mult_t<mult_t<e1_t,e2_t>::type,mult_t<e1_t,e2_t>::type>::type
	                  ,mult_t<mult_t<mult_t<e1_t,e2_t>::type,e1_t>::type,e2_t>::type 
					  >();
	static_check_equal<mult_t<e1_t,mult_t<e1_t,e2_t>::type>::type
	                  ,e2_t
					  >();
	static_check_equal<mult_t<mult_t<e1_t,e2_t>::type,e2_t>::type
	                  ,e1_t
					  >();
	static_check_equal<mult_t<mult_t<e1_t,e2_t>::type,mult_t<e1_t,e2_t>::type>::type
	                  ,minus_one_t<group::identity_t<mult_t>>
					  >();
	static_check_equal<mult_t<mult_t<e2_t,e1_t>::type,mult_t<e2_t,e1_t>::type>::type
	                  ,minus_one_t<group::identity_t<mult_t>>
					  >();
	f((e1_t*)nullptr);
	return 0;
}

