#include"operation.h"
#include"rational.h"

int main(){
	using namespace symbolic;
	std::cout<<exp(integer<3>)<<std::endl;
	std::cout<<sin(integer<3>)<<std::endl;
	std::cout<<nth_root<2>(integer<4>)<<std::endl;
	std::cout<<nth_root<3>(integer<4>)<<std::endl;
	std::cout<<nth_root<4>(integer<4>)<<std::endl;
	std::cout<<nth_root<5>(integer<4>)<<std::endl;
	std::cout<<pow<2>(integer<4>)<<std::endl;
	std::cout<<pow<3>(integer<4>)<<std::endl;
	std::cout<<pow<4>(integer<4>)<<std::endl;
	std::cout<<pow<5>(integer<4>)<<std::endl;
	std::cout<<square(sin(sqrt(integer<4>)))<<std::endl;
	return 0;
}

