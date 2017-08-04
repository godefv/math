#include"ordering.h"
#include"commutation.h"

struct operation_t{};

int main(){
	static_assert(static_compare(group::indexed_element_t<1>{}, group::indexed_element_t<1>{})==0);
	static_assert(static_compare(group::indexed_element_t<2>{}, group::indexed_element_t<1>{})<0);
	static_assert(static_compare(group::indexed_element_t<1>{}, group::indexed_element_t<2>{})>0);

	static_assert(static_compare(group::generated_inverse_t<operation_t, int>{}, group::generated_minus_t<operation_t, int>{})>0);
	static_assert(static_compare(group::generated_inverse_t<operation_t, int>{}, group::generated_element_t<operation_t, int, int>{})>0);
	static_assert(static_compare(group::generated_inverse_t<operation_t, int>{}, group::identity_t<operation_t>{})<0);
	static_assert(static_compare(group::generated_inverse_t<operation_t, int>{}, group::indexed_element_t<2>{})<0);

	static_assert(group::static_compare(operation_t{}, operation_t{})==0);
	static_assert(static_compare(group::identity_t<operation_t>{}, group::identity_t<operation_t>{})==0);

	static_assert(static_compare(group::generated_element_t<operation_t, group::indexed_element_t<2>, group::indexed_element_t<1> >{}
	                            ,group::generated_element_t<operation_t, group::indexed_element_t<1>, group::indexed_element_t<2> >{}
	                            )<0);
	static_assert(static_compare(group::generated_element_t<operation_t, group::indexed_element_t<1>, group::indexed_element_t<2> >{}
	                            ,group::generated_element_t<operation_t, group::indexed_element_t<2>, group::indexed_element_t<1> >{}
	                            )>0);
	static_assert(static_compare(group::generated_element_t<operation_t, group::indexed_element_t<1>, group::indexed_element_t<2> >{}
	                            ,group::generated_element_t<operation_t, group::indexed_element_t<1>, group::indexed_element_t<3> >{}
	                            )>0);
	static_assert(static_compare(group::generated_element_t<operation_t, group::indexed_element_t<1>, group::indexed_element_t<3> >{}
	                            ,group::generated_element_t<operation_t, group::indexed_element_t<1>, group::indexed_element_t<2> >{}
	                            )<0);
	
	return 0;
}

