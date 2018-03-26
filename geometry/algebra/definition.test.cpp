#include"definition.h"
#include"../../symbolic/unit_test.h"

//generators
using e1_t=math::geometry::direction_positive_t<1>;
using e2_t=math::geometry::direction_positive_t<2>;
using e3_t=math::geometry::direction_negative_t<3>;
static constexpr auto e1=e1_t{};
static constexpr auto e2=e2_t{};
static constexpr auto e3=e3_t{};
using math::one;

int main(){
	//powers
	check_equal(e1*e1, one);
	check_equal(e2*e2, one);
	//inverse of generators
	check_equal(inverse(e1),  e1);
	check_equal(inverse(e3), -e3);
	check_equal(inverse(e1*e2), inverse(e2)*inverse(e1));
	//inverse of inverse
	check_equal(inverse(inverse(e1)), e1);
	check_equal(inverse(inverse(e3)), e3);
	//identity
	check_equal(one, inverse(one));
	check_equal(one*e1, e1);
	check_equal(e1*one, e1);
	//minus
	check_equal(inverse(-e1), -inverse(e1));
	//associativity 
	check_equal(e2*(e1*e2), (e2*e1)*e2);
	//1(12)
	check_equal(e1*(e1*e2), e2);
	//(12)2
	check_equal((e1*e2)*e2, e1);
	//commutativity
	//21
	static_assert(static_compare(e2,e1)<0);
	check_equal(e1*e2, -(e2*e1));
	check_equal(e2*e1, -(e1*e2));
	//(12)1
	check_equal((e1*e2)*e1, -(e1*(e1*e2)));
	check_equal((e1*e2)*e1, -e2);
	//(21)1
	check_equal((e2*e1)*e1, -((e1*e2)*e1));
	check_equal((e2*e1)*e1, e2);
	//(12)(12)
	check_equal((e1*e2)*(e1*e2), ((e1*e2)*e1)*e2);
	check_equal((e1*e2)*(e1*e2), -one);
	//(21)(21)
	check_equal((e2*e1)*(e2*e1), -one);
	//(21)(12)
	check_equal((e2*e1)*(e1*e2), ((e2*e1)*e1)*e2);
	check_equal((e2*e1)*(e1*e2), one);

	return 0;
}

