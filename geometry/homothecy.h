#ifndef GEOMETRY_HOMOTHECY_H
#define GEOMETRY_HOMOTHECY_H 

#include<type_traits>

namespace math::geometry{
	template<class ScalarT=double>
	struct homothecy_t{
		ScalarT ratio;
		auto constexpr operator()(KVector<1> const& a){
			return ratio*a;
		}
	};

	template<class ScalarT>
	homothecy_t(ScalarT const&)->homothecy_t<ScalarT>;

	std::ostream& operator<<(std::ostream& out, homothecy_t<auto> const& t){
		return out<<"homothecy{"<<t.ratio<<"}";
	}

	bool constexpr operator==(homothecy_t<auto> const& a, homothecy_t<auto> const& b){
		return a.ratio==b.ratio;
	}
	bool constexpr operator!=(homothecy_t<auto> const& a, homothecy_t<auto> const& b){
		return !(a==b);
	}
	//std::strong_equality operator<=>(homothecy_t const&, homothecy_t const&) = default;

	template<class T> struct is_homothecy:std::false_type{};
	template<class ScalarT> struct is_homothecy<homothecy_t<ScalarT>>:std::true_type{};
	template<class T> concept bool Homothecy=is_homothecy<T>::value;
}

#endif /* GEOMETRY_HOMOTHECY_H */
