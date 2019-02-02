#include"commutator.h"
#include"../symbolic/unit_test.h"

int main(){
	check_equal(commutator(x,y), x*y-y*x);
	check_equal(commutator(k*x+l*y, m*z), (k*m)*commutator(x,z)+(l*m)*commutator(y,z));
	check_equal(commutator(m*z, k*x+l*y), (k*m)*commutator(z,x)+(l*m)*commutator(z,y));
	check_equal(commutator(m,k), math::zero);
	check_equal(math::commutator(2.0,3.0), math::zero);

	return 0;
}

