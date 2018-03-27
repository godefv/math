#include"definition.h"
#include"unit_test.h"

int main(){
	using math::one;
	//powers
	check_equal(e1*e1, one);
	check_equal(e2*e2, one);
	//inverse of generators
	check_equal(inverse(e1),  e1);
	check_equal(inverse(n1), -n1);
	check_equal(inverse(e1*e2), inverse(e2)*inverse(e1));
	//inverse of inverse
	check_equal(inverse(inverse(e1)), e1);
	check_equal(inverse(inverse(n1)), n1);
	//identity
	check_equal(one, inverse(one));
	check_equal(one*e1, e1);
	check_equal(e1*one, e1);
	//minus
	std::cout<<"\nminus:"<<std::endl;
	check_equal(inverse(-e1), -inverse(e1));
	check_equal((-e2)*e2, -(e2*e2));
	check_equal((-(e1*e2))*(e1*e2), -((e1*e2)*(e1*e2)));
	//associativity 
	check_equal(e2*(e1*e2), (e2*e1)*e2);
	//1(12)
	check_equal(e1*(e1*e2), e2);
	//(12)2
	check_equal((e1*e2)*e2, e1);
	//commutativity
	std::cout<<"\ncommutativity:"<<std::endl;
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

