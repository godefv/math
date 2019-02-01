#include"slice.h"
#include"../algebra/unit_test.h"

int main(){
	auto constexpr slice12 =math::geometry::plane(e1,e2);
	auto constexpr slice132=math::geometry::slice_t(e1,n1,e2);

	auto constexpr blade12 =slice12 .blade(); unused(blade12);
	auto constexpr blade132=slice132.blade(); unused(blade132);

	std::cout<<slice12 <<std::endl;
	std::cout<<slice132<<std::endl;

	return 0;
}

