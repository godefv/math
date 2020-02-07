#ifndef CPP20_ARRAY_H
#define CPP20_ARRAY_H 

#include<array>
#include<utility>
#include<type_traits>

namespace std20{
	namespace detail {
		template <class T, std::size_t N, std::size_t... I>
		constexpr std::array<std::remove_cv_t<T>, N>
		to_array_impl(T (&&a)[N], std::index_sequence<I...>)
		{
			return { {std::move(a[I])...} };
		}
	}

	template <class T, std::size_t N>
	constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&&a)[N])
	{
		return detail::to_array_impl(std::move(a), std::make_index_sequence<N>{});
	}
}

#endif /* CPP20_ARRAY_H */
