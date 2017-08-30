#include"slice.h"
#include"../unit_test.h"

static constexpr auto e1=vector::basis_element_t{group::geometric::direction_positive_t<1>{}, 1.};
static constexpr auto e2=vector::basis_element_t{group::geometric::direction_positive_t<2>{}, 1.};
static constexpr auto e3=vector::basis_element_t{group::geometric::direction_negative_t<3>{}, 1.};

int main(){
	auto constexpr slice12 =geometry::plane(e1,e2);
	auto constexpr slice132=geometry::slice_t(e1,e3,e2);

	auto constexpr blade12 =slice12 .blade(); unused(blade12);
	auto constexpr blade132=slice132.blade(); unused(blade132);

	std::cout<<slice12 <<std::endl;
	std::cout<<slice132<<std::endl;

	return 0;
}

