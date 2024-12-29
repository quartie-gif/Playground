#include "HttpServer.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "Logger/Logger.hpp"

HttpServer::HttpServer(int port, const std::shared_ptr<Logger>& logger)
    : m_logger(logger), m_port(port), m_running(false), m_server_fd(-1) {

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(port);
}

HttpServer::~HttpServer() {
    stop();
}

void HttpServer::start() {
    if (m_running) {
        LOG_ERROR(m_logger, "Server is already runnning!");
        return;
    }

    m_server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_fd < 0) {
        LOG_ERROR(m_logger, "Socket creation failed");
        return;
    }

    if (bind(m_server_fd, (struct sockaddr*)&m_address, sizeof(m_address)) <
        0) {
        LOG_ERROR(m_logger, "Bind failed");
        return;
    }

    if (listen(m_server_fd, 3) < 0) {
        LOG_ERROR(m_logger, "Listen failed");
        return;
    }

    m_running = true;
    LOG_INFO(m_logger, "Server is running on http://localhost:{}", m_port);

    while (m_running) {
        int client_socket = accept(m_server_fd, NULL, NULL);
        if (client_socket < 0) {
            LOG_ERROR(m_logger, "Accept failed");
            continue;
        }

        handleRequest(client_socket);
        close(client_socket);
    }
}

void HttpServer::stop() {
    LOG_WARN(m_logger, "Stopping...");
    if (!m_running)
        return;

    m_running = false;
    close(m_server_fd);
    LOG_INFO(m_logger, "Server stopped.");
}

void HttpServer::handleRequest(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));

    std::string request(buffer);
    LOG_INFO(m_logger, "Request received: {}", request);

    std::string response_body = parseRequest(request);
    sendResponse(client_socket, response_body);
}

void HttpServer::sendResponse(int client_socket, const std::string& body) {
    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n"
        "\r\n" +
        body;

    send(client_socket, response.c_str(), response.size(), 0);
}

std::string HttpServer::parseRequest(const std::string& request) {
    if (request.find("GET / HTTP/1.1") != std::string::npos) {
        return "<html><body><h1>Hello, World!</h1></body></html>";
    }
    return "<html><body><h1>404 Not Found</h1></body></html>";
}
