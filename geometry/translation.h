#ifndef GEOMETRY_TRANSLATION_H
#define GEOMETRY_TRANSLATION_H 

namespace math::geometry{
	template<KVector<1> VectorT>
	struct translation_t{
		VectorT vector;
		auto constexpr operator()(KVector<1> const& operand) const{
			return vector+operand;
		}
	};

	template<KVector<1> VectorT>
	translation_t(VectorT const&)->translation_t<VectorT>;

	std::ostream& operator<<(std::ostream& out, translation_t<auto> const& t){
		return out<<"translation{"<<t.vector<<"}";
	}

	template<class> struct is_translation:std::false_type{};
	template<KVector<1> VectorT>
	struct is_translation<translation_t<VectorT>>:std::true_type{};
	template<class T> concept bool Translation=is_translation<T>::value;
}

#endif /* GEOMETRY_TRANSLATION_H */
