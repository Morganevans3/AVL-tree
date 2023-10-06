cmake_minimum_required(VERSION 3.26)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG     v3.4.0)
FetchContent_MakeAvailable(Catch2)

include_directories(test-unit)

add_executable(Main
        src/main.cpp
        src/avl.cpp
        src/avl.h
)

add_executable(Tests
        test-unit/test.cpp
        src/avl.cpp
        src/avl.h
)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)

