#include"definition.h"
#include"unit_test.h"

int main(){
	using math::one;
	using math::zero;
	using math::integer;

	//addition
	check_equal(e0+1.2*e0, 2.2*e0);

	//powers
	check_equal(square(e1), one);
	check_equal(square(e2), one);
	check_equal(square(e1*e2), -one);
	check_equal(square(e1*n1), one);
	check_equal(square((e1+n1)*e2), zero);
	check_equal(square(1.2*e1*e2), -1.2*1.2);
	check_equal(square(1.2*e1*n1), 1.2*1.2);
	//check_equal(square(1.2*(e1+n1)*e2) , zero);

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
	//addition commutativity
	std::cout<<"\naddition commutativity:"<<std::endl;
	check_equal(e1-e2, -e2+e1);
	check_equal(n1-e2, -e2+n1);
	//multiplication commutativity
	std::cout<<"\nmultiplication commutativity:"<<std::endl;
	//21
	static_assert(static_compare(math::mult_operation_t{},e2,e1)<0);
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

	//concepts
	using math::geometry::Blade;
	std::cout<<"\nBlade concept:"<<std::endl;
	check_equal(Blade<int>                                               , true);
	check_equal(Blade<e1_t>                                              , true);
	check_equal(Blade<e2_t>                                              , true);
	check_equal(Blade<std::decay_t<decltype(e1*e2)>>                     , true);
	check_equal(Blade<std::decay_t<decltype(e1*e2*e3)>>                  , true);
	check_equal(Blade<std::decay_t<decltype(integer<5>*e1*e2*e3)>>       , true);
	check_equal(Blade<std::decay_t<decltype(e1+e2)>>                     , false);
	check_equal(Blade<std::decay_t<decltype(e1*(e2+e3))>>                , false);

	using math::geometry::MultiVector;
	std::cout<<"\nMultiVector concept:"<<std::endl;
	check_equal(MultiVector<int>                                         , true);
	check_equal(MultiVector<e1_t>                                        , true);
	check_equal(MultiVector<e2_t>                                        , true);
	check_equal(MultiVector<std::decay_t<decltype(e1*e2)>>               , true);
	check_equal(MultiVector<std::decay_t<decltype(e1*e2*e3)>>            , true);
	check_equal(MultiVector<std::decay_t<decltype(integer<5>*e1*e2*e3)>> , true);
	check_equal(MultiVector<std::decay_t<decltype(e1+e2)>>               , true);
	check_equal(MultiVector<std::decay_t<decltype(e1*(e2+e3))>>          , true);

	return 0;
}

