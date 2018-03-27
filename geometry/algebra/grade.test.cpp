#include"grade.h"
#include"unit_test.h"

int main(){
	using math::geometry::grade;
	using math::geometry::grades;
	using math::geometry::project;
	using math::integer;
	using math::one;
	using math::zero;

	//grade
	check_equal(grade(e1), 1);
	check_equal(grade(n1), 1);
	check_equal(grade(e1*e2), 2);
	check_equal(grade(e1*n1), 2);
	//grades
	check_equal(grades(one)            , grades<0>());
	check_equal(grades(e1)             , grades<1>());
	check_equal(grades(e1*e1)          , grades<0>());
	check_equal(grades(e1*e2)          , grades<2>());
	check_equal(grades(e1*e2+e1*n1)    , grades<2>());
	check_equal(grades(e1*e2*n1)       , grades<3>());
	check_equal(grades(one+e2+e1*e2*n1), grades<0,1,3>());
	//project
	check_equal(project(e1*e1, grades<2>()), zero);
	check_equal(project(one+e1, grades<1>()), e1);
	check_equal(project(one+e1, grades<0>()), one);
	check_equal(project(one+e1+e1*e2, grades<0,2>()), one+e1*e2);
	check_equal(project(one+e1+e1*e2, grades<0,3>()), one);

	using math::geometry::KBlade;
	std::cout<<"\nKBlade concept:"<<std::endl;
	check_equal(KBlade<std::decay_t<decltype(1                  )>, 2>   , false);
	check_equal(KBlade<std::decay_t<decltype(e1                 )>, 2>   , false);
	check_equal(KBlade<std::decay_t<decltype(e2                 )>, 2>   , false);
	check_equal(KBlade<std::decay_t<decltype(e1*e2              )>, 2>   , true);
	check_equal(KBlade<std::decay_t<decltype(e1*e2*e3           )>, 2>   , false);
	check_equal(KBlade<std::decay_t<decltype(integer<5>*e1*e2*e3)>, 2>   , false);
	check_equal(KBlade<std::decay_t<decltype(e1+e2              )>, 2>   , false);
	check_equal(KBlade<std::decay_t<decltype(e1*(e2+e3)         )>, 2>   , false);

	using math::geometry::BiVector;
	std::cout<<"\nBiVector concept:"<<std::endl;
	check_equal(BiVector<int>                                            , false);
	check_equal(BiVector<e1_t>                                           , false);
	check_equal(BiVector<e2_t>                                           , false);
	check_equal(BiVector<std::decay_t<decltype(e1*e2)>>                  , true);
	check_equal(BiVector<std::decay_t<decltype(e1*e2*e3)>>               , false);
	check_equal(BiVector<std::decay_t<decltype(integer<5>*e1*e2*e3)>>    , false);
	check_equal(BiVector<std::decay_t<decltype(e1+e2)>>                  , false);
	check_equal(BiVector<std::decay_t<decltype(e1*(e2+e3))>>             , true);

	return 0;
}

