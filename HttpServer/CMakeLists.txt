cmake_minimum_required(VERSION 3.22)
project(HttpServer LANGUAGES CXX)

include_directories(include)
add_subdirectory(src)

if(ENABLE_TESTS)
    add_subdirectory(tests)
endif()