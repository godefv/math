#include"morphism.h"
#include"unit_test.h"

template<class T> struct f_t{T operand;};
template<class T> f_t(T)->f_t<T>;

namespace math{
template<Symbol SymbolT> struct is_symbol<f_t<SymbolT>>:std::true_type{};
}

bool operator==(f_t<auto> const& a, f_t<auto> const& b){
	return false;
}
template<class T>
bool operator==(f_t<T> const& a, f_t<T> const& b){
	return a.operand==b.operand;
}
bool operator!=(f_t<auto> const& a, f_t<auto> const& b){
	return !(a==b);
}
std::ostream& operator<<(std::ostream& out, f_t<auto> const& a){
	return out<<"f("<<a.operand<<")";
}

auto f=math::group::endomorphism(op, [](auto const& a){return f_t{a};});

int main(){
	//product
	check_equal(f(x*y), f(x)*f(y));
	check_equal(f(x*y*z), f(x)*f(y)*f(z));
	check_equal(f(x*y*x), f(x)*f(y)*f(x));
	//power
	check_equal(f(x*x), f(x)*f(x));
	check_equal(f(x*x*x*x*x), f(x)*f(x)*f(x)*f(x)*f(x));
	//identity
	check_equal(f(id), id);

	return 0;
}

