#ifndef ORDERING_H
#define ORDERING_H 

#include"identity.h"
#include"minus.h"
#include"inverse.h"
#include"operation.h"

namespace group{
	int constexpr ordering(identity_t<auto> const&){
		return 0;
	}
	int constexpr ordering(auto const&){
		return 1;
	}
	int constexpr ordering(generated_inverse_t<auto, auto> const&){
		return 2;
	}
	int constexpr ordering(generated_element_t<auto, auto, auto> const&){
		return 3;
	}
	int constexpr ordering(generated_minus_t<auto, auto> const&){
		return 4;
	}

	int constexpr static_compare(auto const& a, auto const& b){
		return ordering(b)-ordering(a);
	}

	auto constexpr static_compare(identity_t<auto> const& a, identity_t<auto> const& b){
		return static_compare(a.operation,b.operation);
	}
	auto constexpr static_compare(generated_inverse_t<auto, auto> const& a, generated_inverse_t<auto, auto> const& b){
		auto constexpr operation_order=static_compare(a.operation,b.operation);
		if constexpr(operation_order!=0) return operation_order;

		return static_compare(a.value_before_inverse,b.value_before_inverse);
	}
	auto constexpr static_compare(generated_element_t<auto, auto, auto> const& a, generated_element_t<auto, auto, auto> const& b){
		auto constexpr operation_order=static_compare(a.operation,b.operation);
		if constexpr(operation_order!=0) return operation_order;

		auto first_order=static_compare(a.first,b.first);
		if(first_order!=0) return first_order;

		return static_compare(a.second, b.second);
	}
	auto constexpr static_compare(generated_minus_t<auto, auto> const& a, generated_minus_t<auto, auto> const& b){
		auto constexpr operation_order=static_compare(a.operation,b.operation);
		if constexpr(operation_order!=0) return operation_order;

		return static_compare(a.value, b.value);
	}
}

#endif /* ORDERING_H */
