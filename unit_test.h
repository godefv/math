#ifndef UNIT_TEST_H
#define UNIT_TEST_H 

#include<iostream>

template<class T>
void check_equal(T const& a, T const& b){
	if(a!=b){
		std::cerr<<a<<" != "<<b<<std::endl;
		std::exit(1);
	}else{
		std::cerr<<a<<" == "<<b<<std::endl;
	}
}

void print_type(auto const& a){
	std::cout<<typeid(a).name()<<std::endl;
}

#endif /* UNIT_TEST_H */
