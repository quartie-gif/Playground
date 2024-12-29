set(SOURCES
    Logger.cpp
)

add_library(Logger SHARED ${SOURCES})

target_include_directories(Logger PUBLIC
    ${CMAKE_SOURCE_DIR}/Logger/include
)

message(STATUS "Include directories for HttpServer: ${CMAKE_SOURCE_DIR}/Logger/include")

find_package(spdlog REQUIRED)
target_link_libraries(Logger PUBLIC spdlog::spdlog)