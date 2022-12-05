cmake_minimum_required(VERSION 3.23)
project(gb_hard_moments)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

#add_subdirectory(Google_tests)
# добавляем GTests
# GoogleTest requires at least C++14

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        gb_hard_moments
        main.cpp lesson2.cpp lesson1.cpp lesson3.cpp lesson4.cpp lesson5.cpp lesson6.cpp lesson7.cpp lesson8.cpp
        lesson1.h)

target_link_libraries(
        gb_hard_moments
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(gb_hard_moments)







