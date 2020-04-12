#include"to_dense_tensor.h"
#include"unit_test.h"

int main(){
	namespace hana=boost::hana;
	using math::zero;
	using math::one;

	check_equal(math::to_dense_tensor(e1+2.0*e2, hana::make_tuple(e2,e1)), math::dense_tensor_t{hana::make_tuple(hana::make_tuple(e2,e1)), std20::make_array(2.0,1.0)});
	check_equal(math::to_dense_tensor(e1*f2, hana::make_tuple(e1,e2), hana::make_tuple(f1,f2)), math::dense_tensor_t{
		hana::make_tuple(hana::make_tuple(e1,e2), hana::make_tuple(f1,f2)),
		std20::make_array(
			std20::make_array(0.0, 1.0), 
			std20::make_array(0.0, 0.0)
		)}
	);
	check_equal(math::to_dense_tensor(4*e1*f2*g1+2.0f*e2*f1*g1, hana::make_tuple(e1,e2), hana::make_tuple(f1,f2), hana::make_tuple(g1,g2)), 
		math::dense_tensor_t{hana::make_tuple(hana::make_tuple(e1,e2), hana::make_tuple(f1,f2), hana::make_tuple(g1,g2)),
		std20::make_array(
			std20::make_array(std20::make_array(0.0,0.0), std20::make_array(4.0,0.0)), 
			std20::make_array(std20::make_array(2.0,0.0), std20::make_array(0.0,0.0))
		)}
	);

	return 0;
}

