#ifndef GROUP_H
#define GROUP_H 

#include"operation.h"

#include<boost/hana.hpp>
#include<iostream>

namespace hana=boost::hana;

namespace group{
	constexpr auto add_inverses(auto const& set_of_elements, auto const& inverse_operator){
		return hana::fold(set_of_elements, set_of_elements, [&](auto&& extended_set, auto const& e){
			return hana::insert(extended_set, inverse_operator(e));
		});
	}

	constexpr auto add_procucts(auto const& set_of_elements, auto const& operation){
		return hana::fold(set_of_elements, set_of_elements, [&](auto&& extended_set1, auto const& e1){
			return hana::fold(set_of_elements, extended_set1, [&](auto&& extended_set2, auto const& e2){
				return hana::insert(extended_set2, operation(e1,e2));
			});
		});
	}

	constexpr auto generate(auto const& set_of_elements, auto const& inverse_operator, auto const& operation){
		auto extend=[&](auto&& set){return add_procucts(add_inverses(set, inverse_operator), operation);};
		return hana::second(hana::while_(
			  hana::fuse([](auto const& set, auto const& extended_set){return set!=extended_set;})
			, hana::make_pair(set_of_elements, extend(set_of_elements))
			, hana::fuse([&](auto&&, auto&& set){return hana::make_pair(set, extend(set));}
		)));
	}
}

#endif /* GROUP_H */
