cmake_minimum_required(VERSION 3.16)

project(order-book-simulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(orderbook INTERFACE)

target_include_directories(orderbook
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(order-book-simulator src/main.cpp)

target_link_libraries(order-book-simulator PRIVATE orderbook)


# GoogleTest
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests
    tests/main.cpp
)

target_link_libraries(tests
    PRIVATE orderbook
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
