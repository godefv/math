#include"ordering.h"
#include"../geometry/direction.h"

struct operation_t{};

int main(){
	static_assert(static_compare(geometry::direction_t<1>{}, geometry::direction_t<1>{})==0);
	static_assert(static_compare(geometry::direction_t<2>{}, geometry::direction_t<1>{})<0);
	static_assert(static_compare(geometry::direction_t<1>{}, geometry::direction_t<2>{})>0);

	using namespace group;
	static_assert(static_compare(generated_inverse_t<operation_t, int>{}, generated_minus_t<operation_t, int>{})>0);
	static_assert(static_compare(generated_inverse_t<operation_t, int>{}, generated_element_t<operation_t, int, int>{})>0);
	static_assert(static_compare(generated_inverse_t<operation_t, int>{}, identity_t<operation_t>{})<0);
	static_assert(static_compare(generated_inverse_t<operation_t, int>{}, geometry::direction_t<2>{})<0);

	static_assert(static_compare(operation_t{}, operation_t{})==0);
	static_assert(static_compare(identity_t<operation_t>{}, identity_t<operation_t>{})==0);

	static_assert(static_compare(group::generated_element_t<operation_t, geometry::direction_t<2>, geometry::direction_t<1> >{}
	                            ,group::generated_element_t<operation_t, geometry::direction_t<1>, geometry::direction_t<2> >{}
	                            )<0);
	static_assert(static_compare(group::generated_element_t<operation_t, geometry::direction_t<1>, geometry::direction_t<2> >{}
	                            ,group::generated_element_t<operation_t, geometry::direction_t<2>, geometry::direction_t<1> >{}
	                            )>0);
	static_assert(static_compare(group::generated_element_t<operation_t, geometry::direction_t<1>, geometry::direction_t<2> >{}
	                            ,group::generated_element_t<operation_t, geometry::direction_t<1>, geometry::direction_t<3> >{}
	                            )>0);
	static_assert(static_compare(group::generated_element_t<operation_t, geometry::direction_t<1>, geometry::direction_t<3> >{}
	                            ,group::generated_element_t<operation_t, geometry::direction_t<1>, geometry::direction_t<2> >{}
	                            )<0);
	
	return 0;
}

