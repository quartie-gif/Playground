set(SOURCES
    main.cpp
    HttpServer.cpp
    HttpServer.hpp
    IHttpRequestParser.hpp
    HttpRequestParser.hpp
    RequestHandler.hpp
    IRequestHandler.hpp
    HttpRequest.hpp
)

add_executable(HttpServer ${SOURCES})
target_link_libraries(HttpServer PRIVATE Logger)

target_include_directories(HttpServer PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)


