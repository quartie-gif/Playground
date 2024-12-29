#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <Logger/Logger.hpp>
#include <memory>
#include <string>

class HttpServer {
   public:
    HttpServer(int port, const std::shared_ptr<Logger>& logger);
    ~HttpServer();

    void start();
    void stop();

   private:
    std::shared_ptr<Logger> m_logger;
    int m_port;
    bool m_running;
    int m_server_fd;
    struct sockaddr_in m_address;

    void handleRequest(int client_socket);
    void sendResponse(int client_socket, const std::string& body);
    std::string parseRequest(const std::string& request);
};