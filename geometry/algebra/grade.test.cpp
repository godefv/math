#include"grade.h"
#include"../../unit_test.h"

//generators
using e1_t=math::geometry::direction_positive_t<1>;
using e2_t=math::geometry::direction_positive_t<2>;
using e3_t=math::geometry::direction_negative_t<3>;
static constexpr auto e1=e1_t{};
static constexpr auto e2=e2_t{};
static constexpr auto e3=e3_t{};

int main(){
	using math::geometry::grade;
	using math::geometry::grades;
	using math::geometry::project;
	using math::one;
	using math::zero;

	//grade
	check_equal(grade(e1), 1);
	check_equal(grade(e3), 1);
	check_equal(grade(e1*e2), 2);
	check_equal(grade(e1*e3), 2);
	//grades
	check_equal(grades(one)            , grades<0>());
	check_equal(grades(e1)             , grades<1>());
	check_equal(grades(e1*e1)          , grades<0>());
	check_equal(grades(e1*e2)          , grades<2>());
	check_equal(grades(e1*e2+e1*e3)    , grades<2>());
	check_equal(grades(e1*e2*e3)       , grades<3>());
	check_equal(grades(one+e2+e1*e2*e3), grades<0,1,3>());
	//project
	check_equal(project(e1*e1, grades<2>()), zero);
	check_equal(project(one+e1, grades<1>()), e1);
	check_equal(project(one+e1, grades<0>()), one);
	check_equal(project(one+e1+e1*e2, grades<0,2>()), one+e1*e2);
	check_equal(project(one+e1+e1*e2, grades<0,3>()), one);
	return 0;
}

