#ifndef UNIT_TEST_H
#define UNIT_TEST_H 

#include<boost/hana.hpp>
#include<iostream>

namespace boost::hana{
	template<class T, class... Ts>
	std::ostream& operator<<(std::ostream& out, tuple<T, Ts...> const& foldable){
		out<<"<"<<front(foldable);
		return fold(drop_front(foldable), std::cout, [](std::ostream& o, auto const& value){return o<<value<<", ";})<<">";
	}
}

template<class T>
void check_equal(T const& a, T const& b){
	if(a!=b){
		std::cerr<<a<<" != "<<b<<std::endl;
		std::exit(1);
	}else{
		std::cerr<<a<<" == "<<b<<std::endl;
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

void print_type(auto const& a){
	std::cout<<typeid(a).name()<<std::endl;
}

inline auto unused(auto const& a){ static_cast<void>(a); }

#endif /* UNIT_TEST_H */
