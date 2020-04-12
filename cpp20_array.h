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

	//std::make_array
	namespace details {
		template<class> struct is_ref_wrapper : std::false_type {};
		template<class T> struct is_ref_wrapper<std::reference_wrapper<T>> : std::true_type {};

		template<class T>
		using not_ref_wrapper = std::negation<is_ref_wrapper<std::decay_t<T>>>;

		template <class D, class...> struct return_type_helper { using type = D; };
		template <class... Types>
		struct return_type_helper<void, Types...> : std::common_type<Types...> {
			static_assert(std::conjunction_v<not_ref_wrapper<Types>...>,
					"Types cannot contain reference_wrappers when D is void");
		};

		template <class D, class... Types>
		using return_type = std::array<typename return_type_helper<D, Types...>::type, sizeof...(Types)>;
	}

	template < class D = void, class... Types>
	constexpr details::return_type<D, Types...> make_array(Types&&... t) {
		return {std::forward<Types>(t)... };
	}
}

#endif /* CPP20_ARRAY_H */
