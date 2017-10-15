#include"operation.h"
#include"rational.h"

int main(){
	using namespace symbolic;
	std::cout<<exp(integer<3>)<<std::endl;
	std::cout<<sin(integer<3>)<<std::endl;
	std::cout<<nth_root<2>(integer<5>)<<std::endl;
	std::cout<<nth_root<3>(integer<5>)<<std::endl;
	std::cout<<nth_root<4>(integer<5>)<<std::endl;
	std::cout<<nth_root<5>(integer<5>)<<std::endl;
	std::cout<<pow<2>(integer<5>)<<std::endl;
	std::cout<<pow<3>(integer<5>)<<std::endl;
	std::cout<<pow<4>(integer<5>)<<std::endl;
	std::cout<<pow<5>(integer<5>)<<std::endl;
	std::cout<<pow<ratio_t<2,5>>(integer<5>)<<std::endl;
	std::cout<<square(sin(sqrt(integer<5>)))<<std::endl;
	using namespace symbolic::operators;
	std::cout<<-exp(integer<5>)<<std::endl;
	std::cout<<integer<5>*exp(integer<5>)<<std::endl;
	return 0;
}

