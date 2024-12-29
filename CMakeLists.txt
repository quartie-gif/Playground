cmake_minimum_required(VERSION 3.22)
project(MyProject LANGUAGES CXX)

option(ENABLE_TESTS "Whether to enable tests and require GTest" OFF)

add_subdirectory(HttpServer)
add_subdirectory(Logger)

if(ENABLE_TESTS)
    enable_testing()
endif()