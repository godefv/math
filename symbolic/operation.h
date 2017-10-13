#ifndef SYMBOLIC_OPERATION_H
#define SYMBOLIC_OPERATION_H 

#include"eval.h"
#include<boost/hana.hpp>
#include<iostream>
#include<cmath>

namespace symbolic{
	template<class OperationT, class... OperandsT>
	struct operation_t{
		OperationT operation; 
		boost::hana::tuple<OperandsT...> operands;

		constexpr operation_t()=default;
		constexpr operation_t(OperationT const& operation_in, OperandsT const&... operands_in)
			:operation{operation_in}, operands{boost::hana::make_tuple(operands_in...)}
		{}
	};

	template<class OperationT, class... OperandsT>
	std::ostream& operator<<(std::ostream& out, operation_t<OperationT, OperandsT...> const& operation){
		out<<operation.operation<<"("<<boost::hana::front(operation.operands);
		boost::hana::for_each(boost::hana::drop_front(operation.operands), [&out](auto const& operand){out<<", "<<operand;});
		return out<<")";
	}

#define DEFINE_OPERATION(op, ...) \
	struct op##_t{}; \
	inline std::ostream& operator<<(std::ostream& out, op##_t const){return out<<#op;} \
	template<class... OperandsT> auto constexpr op(OperandsT const&... operands){return operation_t{op##_t{}, operands...};} \
	auto constexpr eval(operation_t<op##_t, auto> const& operand){using std::op; return op(eval(boost::hana::front(operand.operands)));}
	DEFINE_OPERATION(exp)
	DEFINE_OPERATION(log)
	DEFINE_OPERATION(abs)
	DEFINE_OPERATION(sin)
	DEFINE_OPERATION(asin)
	DEFINE_OPERATION(sinh)
	DEFINE_OPERATION(asinh)
	DEFINE_OPERATION(cos)
	DEFINE_OPERATION(acos)
	DEFINE_OPERATION(cosh)
	DEFINE_OPERATION(acosh)
#undef DEFINE_OPERATION
	//pow
	template<std::uintmax_t>
	struct pow_t{};

	template<std::uintmax_t N>
	inline std::ostream& operator<<(std::ostream& out, pow_t<N> const){return out<<N<<"th_power";}
	inline std::ostream& operator<<(std::ostream& out, pow_t<2> const){return out<<"square";}
	inline std::ostream& operator<<(std::ostream& out, pow_t<3> const){return out<<"cube";}

	template<std::uintmax_t N> std::string_view constexpr exponent_string;
	using namespace std::string_view_literals;
	template<> std::string_view constexpr exponent_string<2> ="²"sv;
	template<> std::string_view constexpr exponent_string<3> ="³"sv;
	template<> std::string_view constexpr exponent_string<4> ="⁴"sv;
	template<std::uintmax_t N>
	inline std::ostream& operator<<(std::ostream& out, operation_t<pow_t<N>, auto> const& operation) requires exponent_string<N>.data()!=nullptr {
		return out<<"("<<boost::hana::front(operation.operands)<<")"<<exponent_string<N>;
	}
	
	template<std::uintmax_t N>
	auto constexpr pow(auto const& operand){return operation_t{pow_t<N>{}, operand};}
	auto constexpr square(auto const& operand){return operation_t{pow_t<2>{}, operand};}

	//nth_root
	template<std::uintmax_t>
	struct nth_root_t{};

	template<std::uintmax_t N>
	inline std::ostream& operator<<(std::ostream& out, nth_root_t<N> const){return out<<N<<"th_root";}
	inline std::ostream& operator<<(std::ostream& out, nth_root_t<2> const){return out<<"sqrt";}
	inline std::ostream& operator<<(std::ostream& out, nth_root_t<3> const){return out<<"cubic_root";}
	
	template<std::uintmax_t N>
	inline std::ostream& operator<<(std::ostream& out, operation_t<nth_root_t<N>, auto> const& operation) requires exponent_string<N>.data()!=nullptr {
		return out<<exponent_string<N><<"√("<<boost::hana::front(operation.operands)<<")";
	}

	template<std::uintmax_t N>
	auto constexpr nth_root(auto const& operand){return operation_t{nth_root_t<N>{}, operand};}
	auto constexpr sqrt(auto const& operand){return nth_root<2>(operand);}
	auto constexpr eval(operation_t<nth_root_t<2>, auto> const& operand){
		using std::sqrt; 
		using ::eval;
		return sqrt(eval(boost::hana::front(operand.operands)));}

}

#endif /* SYMBOLIC_OPERATION_H */
