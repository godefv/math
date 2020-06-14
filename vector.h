#ifndef VECTOR_H
#define VECTOR_H 

#include"multiplication/power.h"
#include"multiplication/operation.h"
#include"addition/operation.h"

namespace godefv::math{
	template<class DirectionT, class T> struct is_vector:std::false_type{};
	
	template<class DirectionT> struct is_vector<DirectionT, zero_t    >:std::true_type{};
	template<class DirectionT> struct is_vector<DirectionT, DirectionT>:std::true_type{};

	template<class T, class DirectionT> concept Vector=is_vector<DirectionT,T>::value;

	template<class DirectionT, Vector<DirectionT> VectorT, Scalar ScalarT> struct is_vector<DirectionT, group::generated_by_operation_t<mult_operation_t,ScalarT,VectorT>>:std::true_type{};
	template<class DirectionT, Vector<DirectionT> VectorT, Scalar ScalarT> struct is_vector<DirectionT, group::generated_by_operation_t<mult_operation_t,VectorT,ScalarT>>:std::true_type{};
	template<class DirectionT, Vector<DirectionT> VectorT, Scalar  ScalarT > struct is_vector<DirectionT, group::generated_power_t<add_operation_t,ScalarT,VectorT>>:std::true_type{};
	template<class DirectionT, Vector<DirectionT> Vector1, Vector<DirectionT> Vector2> struct is_vector<DirectionT, group::generated_by_operation_t<add_operation_t,Vector1,Vector2>>:std::true_type{};

	template<class DirectionT>
	auto constexpr coordinate(DirectionT, zero_t){
		return integer<0>;
	}
	template<class DirectionT>
	auto constexpr coordinate(DirectionT, DirectionT){
		return integer<1>;
	}
	template<class DirectionT, Vector<DirectionT> VectorT>
	auto constexpr coordinate(DirectionT d, group::generated_by_operation_t<mult_operation_t,Scalar,VectorT> const& vector){
		return vector.first*coordinate(d, vector.second);
	}
	template<class DirectionT>
	auto constexpr coordinate(DirectionT d, group::generated_by_operation_t<mult_operation_t,Vector<DirectionT>,Scalar> const& vector){
		return coordinate(d, vector.first)*vector.second;
	}
	template<class DirectionT, Vector<DirectionT> VectorT>
	auto constexpr coordinate(DirectionT d, group::generated_power_t<add_operation_t,Scalar,VectorT> const& vector){
		return vector.exponent*coordinate(d, vector.operand);
	}
	template<class DirectionT, Vector<DirectionT> Vector1, Vector<DirectionT> Vector2>
	auto constexpr coordinate(DirectionT d, group::generated_by_operation_t<add_operation_t,Vector1,Vector2> const& vector){
		return coordinate(d, vector.first)+coordinate(d, vector.second);
	}

}

#endif /* VECTOR_H */
