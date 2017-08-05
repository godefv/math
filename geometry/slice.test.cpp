#include"slice.h"

using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_negative_t<3>;

using namespace algebra::geometric::operators;

static constexpr auto e1=1.*e1_t{};
static constexpr auto e2=1.*e2_t{};
static constexpr auto e3=1.*e3_t{};

int main(){
	auto constexpr slice12=geometry::plane(e1,e2);
	auto constexpr slice132=geometry::slice_t(e1,e3,e2);

	auto constexpr blade12=slice12.blade();
	auto constexpr blade132=slice132.blade();

	return 0;
}

