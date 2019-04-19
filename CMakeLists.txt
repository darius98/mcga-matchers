cmake_minimum_required(VERSION 3.12.1)
project(MCGA_matchers)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

option(MCGA_matchers_tests "Build MCGA Matchers tests" OFF)

add_library(mcga_matchers INTERFACE)
target_include_directories(mcga_matchers INTERFACE include)

install(DIRECTORY include DESTINATION .)

if (MCGA_matchers_tests)
    add_executable(mcga_matchers_test
            tests/comparison_test.cpp
            tests/composite_test.cpp
            tests/functional_test.cpp
            tests/iterable_test.cpp
            tests/numeric_test.cpp
            tests/pointer_test.cpp
            tests/string_test.cpp
            tests/truth_test.cpp
            )
    target_link_libraries(mcga_matchers_test mcga_test mcga_matchers)
endif ()
