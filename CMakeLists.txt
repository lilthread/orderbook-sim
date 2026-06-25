cmake_minimum_required(VERSION 3.21)

project(orderbook-simulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(orderbook INTERFACE)

target_include_directories(orderbook
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(client-orderbook src/Client.cpp)
add_executable(Server-orderbook src/Server.cpp)

target_link_libraries(client-orderbook PRIVATE orderbook)
target_link_libraries(Server-orderbook PRIVATE orderbook)

# Tests
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
    PRIVATE
        orderbook
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(tests)
