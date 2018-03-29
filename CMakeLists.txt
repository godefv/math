cmake_minimum_required(VERSION 3.8)
project(math CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0)
	if(DISABLE_COMPILER_CHECK)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" ) 
	else()
		message(FATAL_ERROR "Require at least g++-7.0")
	endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts" ) 

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
find_package(Boost 1.62.0)

enable_testing()

function(math_add_test module)
	string(REPLACE "/" "_" test_target ${module})
	set(test_target "test_${test_target}")
	add_executable(${test_target} ${module}.test.cpp)
	target_compile_options(${test_target} PRIVATE ${GCC_WARNING_FLAGS})
	add_test(${module} ${test_target})
endfunction()

math_add_test(group/power)
math_add_test(group/operation)
math_add_test(group/morphism)
math_add_test(addition/operation)
math_add_test(addition/power)
math_add_test(multiplication/operation)
math_add_test(multiplication/power)
math_add_test(multiplication/reverse)
math_add_test(geometry/algebra/definition)
math_add_test(geometry/algebra/grade)
math_add_test(geometry/algebra/dot_product)
math_add_test(geometry/algebra/wedge_product)
math_add_test(geometry/algebra/norm)
math_add_test(geometry/algebra/exponential)
math_add_test(symbolic/operation)
math_add_test(symbolic/trigonometry)
math_add_test(symbolic/rational)

#math_add_test(geometry/slice)
#math_add_test(geometry/rotation)
#math_add_test(symbolic/exponential)
