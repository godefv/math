#ifndef HANA_PIPE_H
#define HANA_PIPE_H 

#include<boost/hana.hpp>
#include"cpp20_array.h"
#include<type_traits>
#include<concepts>

namespace boost::hana{
	//default pipe operator
	template<class T>
	inline auto constexpr operator|(T const& input, std::invocable<T> auto function){
		return function(input);
	}

	//overload to take precedence over the operator defined for monads
	template <typename Xs, typename = typename std::enable_if<
		detail::monad_operators<typename hana::tag_of<Xs>::type>::value
	>::type>
	constexpr auto operator|(Xs&& input, std::invocable<Xs> auto&& function){
		return function(input);
	}

	template<class F>
	struct transform_with_t{
		F f;
		auto constexpr operator()(auto const& operand) const{
			return transform(operand,f);
		}
	};

	template<class F>
	inline auto constexpr transform_with(F&& f){
		return transform_with_t<F>{std::forward<F>(f)};
	}
	inline auto constexpr fold_with(auto const& f){
		return [&](auto const& x){return fold(x,f);};
	}

	//get by type in tuple
	template <typename T, typename Searchable>
	auto get(Searchable&& xs)
	{
		return *hana::find_if(std::forward<Searchable>(xs), [](auto const& x){
			return hana::equal(hana::decltype_(x), hana::type_c<const T>);
		});
	}

	//to_array, like to_tuple
	template<class T>
	auto constexpr to_array=[](auto const& xs){
		return hana::unpack(xs, [](auto const&... x){return std20::make_array(static_cast<T>(x)...);});
	};

}


#endif /* HANA_PIPE_H */
