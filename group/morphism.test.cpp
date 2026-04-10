#include"morphism.h"
#include"unit_test.h"

template<class X> struct f_t{X operand;};
template<class X> f_t(X)->f_t<X>;

namespace godefv::math{
template<Symbol SymbolT> struct is_symbol<f_t<SymbolT>>:std::true_type{};
}

template<class X1, class X2>
bool operator==(f_t<X1> const& a, f_t<X2> const& b){
	return false;
}
template<class X>
bool operator==(f_t<X> const& a, f_t<X> const& b){
	return a.operand==b.operand;
}
template<class X1, class X2>
bool operator!=(f_t<X1> const& a, f_t<X2> const& b){
	return !(a==b);
}
template<class X>
std::ostream& operator<<(std::ostream& out, f_t<X> const& a){
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

