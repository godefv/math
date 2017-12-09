#ifndef SYMBOLIC_OPERATION_H
#define SYMBOLIC_OPERATION_H 

#include"rational.h"
#include"eval.h"
#include<boost/hana.hpp>
#include<iostream>
#include<cmath>
#include<type_traits>

namespace symbolic{
	template<class OperationT, class... OperandsT>
	struct operation_t{
		OperationT operation; 
		boost::hana::tuple<OperandsT...> operands;

		constexpr operation_t()=default;
		constexpr operation_t(OperationT const& operation_in, OperandsT const&... operands_in)
			:operation{operation_in}, operands{boost::hana::make_tuple(operands_in...)}
		{}

		auto constexpr operand() const{
			return boost::hana::front(operands);
		}
	};

	template<class> struct is_operation:std::false_type{};
	template<class OperationT, class... OperandsT>
	struct is_operation<operation_t<OperationT, OperandsT...>>:std::true_type{};
	template<class T> concept bool Operation=is_operation<T>::value;

	template<class OperationT, class... OperandsT>
	std::ostream& operator<<(std::ostream& out, operation_t<OperationT, OperandsT...> const& operation){
		out<<operation.operation<<"("<<boost::hana::front(operation.operands);
		boost::hana::for_each(boost::hana::drop_front(operation.operands), [&out](auto const& operand){out<<", "<<operand;});
		return out<<")";
	}

#define DEFINE_OPERATION(op) \
	struct op##_t{}; \
	inline std::ostream& operator<<(std::ostream& out, op##_t const){return out<<#op;} \
	template<class... OperandsT> auto constexpr op(OperandsT const&... operands){return operation_t{op##_t{}, operands...};} \
	auto constexpr eval(operation_t<op##_t, auto> const& operand){using std::op; return op(eval(operand.operand()));}
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
	template<Ratio RatioT>
	struct pow_t{RatioT exponent;};
	template<Ratio RatioT>
	using nth_root_t=pow_t<decltype(inverse(RatioT{}))>;

	inline std::ostream& operator<<(std::ostream& out, pow_t<auto> const power_operation){return out<<"power<"<<power_operation.exponent<<">";}
	template<std::intmax_t N>
	inline std::ostream& operator<<(std::ostream& out, pow_t<integer_t<N>> const){return out<<N<<"th_power";}
	inline std::ostream& operator<<(std::ostream& out, pow_t<integer_t<2>> const){return out<<"square";}
	inline std::ostream& operator<<(std::ostream& out, pow_t<integer_t<3>> const){return out<<"cube";}
	template<std::intmax_t N>
	inline std::ostream& operator<<(std::ostream& out, pow_t<ratio_t<1,N>> const){return out<<N<<"th_root";}
	inline std::ostream& operator<<(std::ostream& out, nth_root_t<integer_t<2>> const){return out<<"sqrt";}
	inline std::ostream& operator<<(std::ostream& out, nth_root_t<integer_t<3>> const){return out<<"cubic_root";}

	using namespace std::string_view_literals;
	std::string_view constexpr exponent_string(integer_t<2>){return "²"sv;}
	std::string_view constexpr exponent_string(integer_t<3>){return "³"sv;}
	std::string_view constexpr exponent_string(integer_t<4>){return "⁴"sv;}
	template<Ratio RatioT> requires requires(){exponent_string(RatioT{});}
	inline std::ostream& operator<<(std::ostream& out, operation_t<pow_t<RatioT>, auto> const& operation){
		return out<<"("<<operation.operand()<<")"<<exponent_string(RatioT{});
	}
	template<Ratio RatioT> requires !requires(){exponent_string(RatioT{});} && requires(){exponent_string(inverse(RatioT{}));} 
	inline std::ostream& operator<<(std::ostream& out, operation_t<pow_t<RatioT>, auto> const& operation){
		return out<<exponent_string(inverse(RatioT{}))<<"√("<<operation.operand()<<")";
	}
	
	template<std::intmax_t N>
	auto constexpr pow(auto const& operand){return operation_t{pow_t<integer_t<N>>{}, operand};}
	template<Ratio RatioT>
	auto constexpr pow(auto const& operand){return operation_t{pow_t<RatioT>{}, operand};}
	template<std::intmax_t N>
	auto constexpr nth_root(auto const& operand){return pow<ratio_t<1,N>>(operand);}
	auto constexpr square(auto const& operand){return pow<2>(operand);}
	auto constexpr sqrt(auto const& operand){return nth_root<2>(operand);}

	auto constexpr eval(operation_t<nth_root_t<integer_t<2>>, auto> const& operand){
		using std::sqrt; 
		using ::eval;
		return sqrt(eval(operand.operand()));
	}

	//inverse
	struct inverse_t{};
	inline std::ostream& operator<<(std::ostream& out, inverse_t const){return out<<"inverse";} 
	auto constexpr inverse(auto const& operand){return operation_t{inverse_t{}, operand};} 
	
	template<Ratio RatioT>
	auto constexpr inverse(operation_t<pow_t<RatioT>,auto> const& operand){
		return pow<RatioT>(inverse(operand.operand()));
	} 
	
	auto constexpr eval(operation_t<inverse_t, auto> const& operand){
		auto evaluated_operand=eval(operand.operand());
		if constexpr(std::is_same<decltype(evaluated_operand), double>::value){
			return 1./evaluated_operand;
		}else{
			return inverse(evaluated_operand);
		}
	}

	//minus
	struct minus_t{}; 
	inline std::ostream& operator<<(std::ostream& out, minus_t const){return out<<"minus";} 
	namespace operators{ 
	auto constexpr operator-(auto const& a){return operation_t{minus_t{}, a};} 
	} 
	auto constexpr eval(operation_t<minus_t, auto> const& operand){
		auto evaluated_operand=eval(operand.operand());
		if constexpr(std::is_same<decltype(evaluated_operand), double>::value){
			return -evaluated_operand;
		}else{
			return inverse(evaluated_operand);
		}
	}
}

#endif /* SYMBOLIC_OPERATION_H */
