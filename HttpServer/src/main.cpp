#include "HttpServer.hpp"

int main() {
    auto logger =
        std::make_shared<Logger>("%^[%T] [%l] %v%$", Logger::LogLevel::Debug);
    HttpServer server(8080, logger);

    server.start();

    return 0;
}
