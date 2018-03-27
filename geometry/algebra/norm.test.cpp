#include"norm.h"
#include"unit_test.h"

int main(){
	using math::geometry::norm;
	using math::integer;
	using math::one;
	//generators
	check_equal(norm(e1),one);
	check_equal(norm(e2),one);
	check_equal(norm(e2),one);
	check_equal(norm(n1),one);

	//
	check_equal(norm(integer<5>*e1),integer<5>);
	check_equal(norm(integer<5>*e2),integer<5>);
	check_equal(norm(integer<5>*e2),integer<5>);
	check_equal(norm(integer<5>*n1),integer<5>);
	
	check_equal(norm(k*e1),abs(k));
	check_equal(norm(k*e2),abs(k));
	check_equal(norm(k*e2),abs(k));
	check_equal(norm(k*n1),abs(k));
	
	check_equal(norm(e1*e2),one);
	check_equal(norm(e2*n1),one);
	check_equal(norm(e2*e1*n1),one);

	check_equal(norm(k*e1*e2),abs(k));
	check_equal(norm(k*e2*n1),abs(k));
	check_equal(norm(k*e2*e1*n1),abs(k));
	return 0;
}

