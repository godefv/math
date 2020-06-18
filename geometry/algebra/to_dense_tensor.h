#ifndef GEOMETRY_ALGEBRA_TO_TENSOR_H
#define GEOMETRY_ALGEBRA_TO_TENSOR_H 

#include"dot_product.h"
#include"../../expression.h"
#include"../../hana.h"

namespace godefv::math{
	namespace hana=boost::hana;

	//nested_arrays_t
	template<Number, unsigned long...> struct nested_arrays_helper_t;
	template<Number ValueT, unsigned long... Ns> 
	using nested_arrays_t=typename nested_arrays_helper_t<ValueT, Ns...>::type;

	template<Number ValueT> 
	struct nested_arrays_helper_t<ValueT>{
		using type=ValueT;
	};
	template<Number ValueT, unsigned long N1, unsigned long... OtherNs>
	struct nested_arrays_helper_t<ValueT, N1, OtherNs...>{
		using type=std::array<nested_arrays_t<ValueT, OtherNs...>, N1>;
	};

	//dense_tensor_t
	template<Number ValueT, class... FrameTs>
	struct dense_tensor_t{
		hana::tuple<FrameTs...> frames;
		nested_arrays_t<ValueT, hana::length(FrameTs{})...> data;
	};
	template<class... FrameTs>
	dense_tensor_t(hana::tuple<FrameTs...>, nested_arrays_t<double, hana::length(FrameTs{})...>)->dense_tensor_t<double, FrameTs...>;
	template<class... FrameTs>
	dense_tensor_t(hana::tuple<FrameTs...>, nested_arrays_t<float , hana::length(FrameTs{})...>)->dense_tensor_t<float , FrameTs...>;

	template<Number ValueT, class... FrameTs>
	std::ostream& operator<<(std::ostream& out, dense_tensor_t<ValueT,FrameTs...> const& tensor){
		return out<<tensor.frames<<"\n"<<tensor.data;
	}
	template<Number ValueT, class... FrameTs>
	bool operator==(dense_tensor_t<ValueT,FrameTs...> const& tensor1, dense_tensor_t<ValueT,FrameTs...> const& tensor2){
		return tensor1.data==tensor2.data;
	}
	template<Number ValueT, class... FrameTs>
	bool operator!=(dense_tensor_t<ValueT,FrameTs...> const& tensor1, dense_tensor_t<ValueT,FrameTs...> const& tensor2){
		return !(tensor1==tensor2);
	}


	template<Symbol... SymbolTs, class ValueT=double>
	auto constexpr to_dense_tensor(Expression auto const& expression, hana::tuple<SymbolTs...> frame){
		return dense_tensor_t{
			hana::make_tuple(frame),
			frame
			|hana::transform_with([&expression](auto const& blade){return (expression|inverse(blade));})
			|hana::to_array<ValueT>
		};
	}
	template<Symbol... Symbol1Ts, Symbol... Symbol2Ts, class... OtherFrameTs>
	auto constexpr to_dense_tensor(Expression auto const& expression, hana::tuple<Symbol1Ts...> frame1, hana::tuple<Symbol2Ts...> frame2, OtherFrameTs... other_frames){
		return dense_tensor_t{
			hana::make_tuple(frame1, frame2, other_frames...),
			frame1
			|hana::transform_with([&](auto const& blade1){
				return to_dense_tensor(expression, frame2|hana::transform_with([&](auto const& blade2){return blade1*blade2;}), other_frames...).data;
			})
			|hana::to_array<nested_arrays_t<double, hana::length(frame2), hana::length(other_frames)...>>
		};
	}
}

#endif /* GEOMETRY_ALGEBRA_TO_TENSOR_H */
