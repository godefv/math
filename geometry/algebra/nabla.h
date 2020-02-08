#ifndef GEOMETRY_ALGEBRA_NABLA_H
#define GEOMETRY_ALGEBRA_NABLA_H 

#include"dot_product.h"
#include"grade.h"
#include"reference_frame.h"
#include"../object/direction.h"
#include"../../hana.h"

namespace godefv::math::geometry{
	namespace hana=boost::hana;

	template<Symbol VariableT> requires MultiVector<VariableT> && static_cast<bool>(grades(VariableT{})==grades<1>())
	struct nabla_t{
		VariableT variable;
	};
	template<Symbol VariableT>
	nabla_t(VariableT)->nabla_t<VariableT>;

	//we pretend that nabla is a blade because it is a vector and not a sum
	template<Symbol VariableT> struct is_blade<nabla_t<VariableT>>: std::true_type{};

	//grade
	auto constexpr grade(nabla_t<auto> const&){return 1;}

	//operators
	std::ostream& operator<<(std::ostream& out, nabla_t<auto> const& nabla){
		return out<<"nabla{"<<nabla.variable<<"}";
	}
	bool constexpr operator==(nabla_t<auto> const& a, nabla_t<auto> const& b){
		return a.variable==b.variable;
	}
	bool constexpr operator!=(nabla_t<auto> const& a, nabla_t<auto> const& b){
		return !(a==b);
	}

	auto constexpr operator*(nabla_t<auto> nabla, auto const& operand){
		auto constexpr frame=get_reference_frame(nabla.variable);
		auto constexpr reciprocal_frame=frame|hana::to_tuple|hana::transform_with([&](auto const& direction){return inverse(direction);});
		auto constexpr coordinates=reciprocal_frame|hana::transform_with([&](auto const& direction){return (nabla.variable|direction);});
		return hana::zip(reciprocal_frame, coordinates)
			|hana::transform_with([&](auto const& direction_coordinate){
				using namespace hana::literals;
				auto const& direction =direction_coordinate[0_c];
				auto const& coordinate=direction_coordinate[1_c];
				return direction*differentiate(coordinate,operand);
			})
			|hana::fold_with(add_operation_t{})
		;
	}

}

#endif /* GEOMETRY_ALGEBRA_NABLA_H */
