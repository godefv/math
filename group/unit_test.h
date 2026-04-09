#ifndef GROUP_UNIT_TEST_H
#define GROUP_UNIT_TEST_H

#include"identity.h"
#include"operation.h"
#include"../symbolic/unit_test.h"

#include<type_traits>

struct dummy_operation_t{
	static auto constexpr apply(auto const& a, auto const& b){
		return a*b;
	}
	auto constexpr operator()(auto const& a, auto const& b) const{
		return std::decay_t<decltype(*this)>::apply(a,b);
	}
};
auto constexpr op=dummy_operation_t{};
auto constexpr id=math::group::identity_t<dummy_operation_t>{};

namespace godefv::math{
	template<class A, class B> requires (NonSimpleScalar<A> || NonSimpleScalar<B>)
	auto constexpr operator*(A const& a, B const& b){
		return group::operation(dummy_operation_t{},a,b);
	}
}

struct dummy_plus_operation_t{
	static auto constexpr apply(auto const& a, auto const& b){
		return a+b;
	}
};
auto constexpr plus_op=dummy_plus_operation_t{};

#endif /* GROUP_UNIT_TEST_H */
