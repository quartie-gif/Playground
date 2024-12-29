#include "HttpRequestParser.hpp"
#include "HttpServer.hpp"

int main() {
    auto logger =
        std::make_shared<Logger>("%^[%T] [%l] %v%$", Logger::LogLevel::Info);
    const HttpRequestParser requestParser(logger);

    HttpServer server(8080, logger, requestParser);
    server.start();

    return 0;
}
