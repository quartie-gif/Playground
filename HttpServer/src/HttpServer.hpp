#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <Logger/Logger.hpp>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "HttpRequestParser.hpp"
#include "IHttpRequestParser.hpp"
#include "IRequestHandler.hpp"

class HttpServer {
   public:
    HttpServer(int port, std::shared_ptr<Logger> logger,
               const IHttpRequestParser& requestParser);
    ~HttpServer();

    void start();
    void stop();

   private:
    static inline const int LISTEN_BACKLOG = 3;

    std::shared_ptr<Logger> m_logger;
    const IHttpRequestParser& m_requestParser;
    int m_port;
    bool m_running;
    int m_server_fd;
    struct sockaddr_in m_address;
    std::unordered_map<HttpMethod, std::shared_ptr<IRequestHandler>> m_handlers;

    void handleRequest(int client_socket);
    void sendResponse(int client_socket, const std::string& body);
    std::string handleHttpRequest(const HttpRequest& request);
    void addHandler(HttpMethod method,
                    std::shared_ptr<IRequestHandler> handler);
};
