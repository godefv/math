#ifndef UNIT_TEST_H
#define UNIT_TEST_H 

#include<boost/hana.hpp>
#include<iostream>

namespace boost::hana{
	template<class T, class... Ts>
	std::ostream& operator<<(std::ostream& out, set<T, Ts...> const& foldable){
		out<<"<";
		return fold(foldable, std::cout, [](std::ostream& o, auto const& value)->std::ostream&{return o<<value<<", ";})<<">";
	}
	template<template<class...> class List, class T, class... Ts> requires std::is_same<List<>,tuple<>>::value
	std::ostream& operator<<(std::ostream& out, List<T, Ts...> const& foldable){
		out<<"<"<<front(foldable);
		return fold(drop_front(foldable), std::cout, [](std::ostream& o, auto const& value){return o<<value<<", ";})<<">";
	}
}

void print_type(auto const& a){
	std::cout<<typeid(a).name()<<std::endl;
}

void check_equal(auto const& a, auto const& b){
	std::cerr<<"different types: "<<std::endl;
	std::cerr<<"  "<<typeid(a).name()<<std::endl;
	std::cerr<<"≠ "<<typeid(b).name()<<std::endl;
	std::cerr<<"  "<<a<<std::endl;
	std::cerr<<"≠ "<<b<<std::endl;
	std::exit(1);
}
template<class T>
void check_equal(T const& a, T const& b){
	if(a==b){
		std::cerr<<a<<" == "<<b<<std::endl;
	}else{
		std::cerr<<a<<" != "<<b<<std::endl;
		std::exit(1);
	}
}

template<class T>
void check_less(T const& a, T const& b){
	if(a>b){
		std::cerr<<a<<" > "<<b<<std::endl;
		std::exit(1);
	}else{
		std::cerr<<a<<" < "<<b<<std::endl;
	}
}

inline auto unused(auto const& a){ static_cast<void>(a); }

#endif /* UNIT_TEST_H */
