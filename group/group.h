#ifndef GROUP_H
#define GROUP_H 

#include"operation.h"

#include<boost/hana.hpp>

namespace hana=boost::hana;

namespace group{
	constexpr auto add_inverses(auto const& set_of_elements, auto const& inverse_operator){
		auto extended_set_of_elements=set_of_elements;
		hana::for_each(set_of_elements, [&](auto const& e){
				hana::insert(extended_set_of_elements, inverse_operator(e));
		});
		return extended_set_of_elements;
	}

	constexpr auto add_procucts(auto const& set_of_elements, auto const& operation){
		auto extended_set_of_elements=set_of_elements;
		hana::for_each(set_of_elements, [&](auto const& e1){
			hana::for_each(set_of_elements, [&](auto const& e2){
					hana::insert(extended_set_of_elements, operation(e1,e2));
			});
		});
		return extended_set_of_elements;
	}

	constexpr auto generate_group(auto const& set_of_elements, auto const& inverse_operator, auto const& operation){
		auto group=set_of_elements;
		auto extended_group=add_procucts(add_inverses(group, inverse_operator), operation);
		hana::while_(hana::fuse([](auto const& a, auto const& b){return a!=b;}), hana::make_pair(group, extended_group), hana::fuse([&](auto&& g, auto&& extended_g){
				return hana::make_pair(extended_g, add_procucts(add_inverses(extended_g, inverse_operator), operation));
		}));
		return extended_group;
	}
}

#endif /* GROUP_H */
