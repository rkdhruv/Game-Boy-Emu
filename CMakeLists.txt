cmake_minimum_required(VERSION 3.20)
project(gbemu CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)          # no GNU extensions: portable, standard C++
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # editors + clang-tidy read this

add_library(gb_core src/registers.cpp)
target_include_directories(gb_core PUBLIC include)
target_compile_options(gb_core PUBLIC
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror -g)

option(GB_SANITIZE "Build with ASan + UBSan" ON)
if(GB_SANITIZE)
    target_compile_options(gb_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(gb_core PUBLIC -fsanitize=address,undefined)
endif()

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(gb_tests tests/test_registers.cpp)
target_link_libraries(gb_tests PRIVATE gb_core GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(gb_tests)