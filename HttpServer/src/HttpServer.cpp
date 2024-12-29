#include "HttpServer.hpp"
#include "IRequestHandler.hpp"
#include "RequestHandler.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <functional>
#include <unordered_map>

HttpServer::HttpServer(int port, std::shared_ptr<Logger> logger,
                       const IHttpRequestParser& requestParser)
    : m_logger(logger),
      m_requestParser(requestParser),
      m_port(port),
      m_running(false),
      m_server_fd(-1) {

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(port);

    addHandler(HttpMethod::GET, std::make_shared<GetRequestHandler>(m_logger));
    addHandler(HttpMethod::POST,
               std::make_shared<PostRequestHandler>(m_logger));
    addHandler(HttpMethod::DELETE,
               std::make_shared<DeleteRequestHandler>(m_logger));
}

HttpServer::~HttpServer() {
    stop();
}

void HttpServer::start() {
    if (m_running) {
        LOG_ERROR(m_logger, "Server is already running!");
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

    if (listen(m_server_fd, HttpServer::LISTEN_BACKLOG) < 0) {
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
    HttpRequest http_request = m_requestParser.parseRequest(request);
    std::string response_body = handleHttpRequest(
        http_request);  // TODO: Try to implement WebSocket connection :)  What about the arch? WS is HTTP connection!

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

std::string HttpServer::handleHttpRequest(const HttpRequest& request) {
    auto it = m_handlers.find(request.method);
    if (it != m_handlers.end()) {
        return it->second->handleRequest(request);
    }

    return "<html><body><h1>405 Method Not Allowed</h1></body></html>";
}

void HttpServer::addHandler(HttpMethod method,
                            std::shared_ptr<IRequestHandler> handler) {
    m_handlers[method] = handler;
}
