cmake_minimum_required(VERSION 3.8)
project(math CXX)

if(NOT CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0)
	if(DISABLE_COMPILER_CHECK)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fconcepts" ) 
	else()
		message(FATAL_ERROR "Require at least g++-7.0")
	endif()
endif()

set(GCC_WARNING_FLAGS
    -Werror
    -Wall
    -Wextra
    -Wredundant-decls
    -Wcast-align
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wswitch-enum
    -Wswitch-default
    -Winvalid-pch
    -Wredundant-decls
    -Wformat=2
    -Wmissing-format-attribute
    -Wformat-nonliteral
    -flto
    -Wodr
)

# require hana library, may work with Boost >= 1.61, but was tested only with boost 1.62 and 1.64
find_package(Boost 1.62.0 REQUIRED)

add_library(math INTERFACE)
target_compile_features(math INTERFACE cxx_std_17)
#target_compile_features(math INTERFACE cxx_concepts)
if(CMAKE_COMPILER_IS_GNUCXX)
	target_compile_options(math INTERFACE "-fconcepts")
endif()

enable_testing()

function(math_add_test module)
	string(REPLACE "/" "_" test_target ${module})
	set(test_target "test_${test_target}")
	add_executable(${test_target} ${module}.test.cpp)
	target_link_libraries(${test_target} math)
	target_compile_options(${test_target} PRIVATE ${GCC_WARNING_FLAGS})
	if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
		add_test(${module} ${test_target})
	endif()
endfunction()

math_add_test(group/power)
math_add_test(group/operation)
math_add_test(group/morphism)
math_add_test(addition/operation)
math_add_test(addition/power)
math_add_test(multiplication/operation)
math_add_test(multiplication/power)
math_add_test(multiplication/differentiate)
math_add_test(multiplication/reverse)
math_add_test(multiplication/commutator)
math_add_test(geometry/algebra/definition)
math_add_test(geometry/algebra/grade)
math_add_test(geometry/algebra/dot_product)
math_add_test(geometry/algebra/wedge_product)
math_add_test(geometry/algebra/norm)
math_add_test(geometry/algebra/exponential)
math_add_test(geometry/algebra/nabla)
math_add_test(symbolic/operation)
math_add_test(symbolic/operation/trigonometry)
math_add_test(symbolic/rational)

math_add_test(geometry/object/slice)
math_add_test(geometry/frame/affine_map)
math_add_test(geometry/frame/linear_map)
math_add_test(geometry/frame/orientation)
math_add_test(geometry/frame/placement)
math_add_test(geometry/frame/position)
math_add_test(geometry/vector_transform/rotation)
math_add_test(geometry/vector_transform/scaling)
math_add_test(geometry/vector_transform/projection)
math_add_test(geometry/vector_transform/perspective_projection)
math_add_test(geometry/vector_transform/composition)
math_add_test(geometry/point_transform/from_vector_transform)
math_add_test(geometry/rendering)
#math_add_test(symbolic/exponential)
