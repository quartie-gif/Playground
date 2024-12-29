#pragma once

#include <Logger/Logger.hpp>
#include <memory>

#include "IRequestHandler.hpp"

class GetRequestHandler : public IRequestHandler {
   private:
    std::shared_ptr<Logger> m_logger;

   public:
    GetRequestHandler(std::shared_ptr<Logger> logger) : m_logger(logger) {}

    std::string handleRequest(const HttpRequest& request) override {
        LOG_INFO(m_logger, "--- GET REQUEST --- \n{}", request.to_string());
        if (request.path == "/") {
            return "<html><body><h1>Welcome to the GET "
                   "endpoint</h1></body></html>";
        }
        return "<html><body><h1>404 Not Found</h1></body></html>";
    }
};

class PostRequestHandler : public IRequestHandler {
   private:
    std::shared_ptr<Logger> m_logger;

   public:
    PostRequestHandler(std::shared_ptr<Logger> logger) : m_logger(logger) {}

    std::string handleRequest(const HttpRequest& request) override {
        LOG_INFO(m_logger, "--- GET REQUEST --- \n{}", request.to_string());
        if (request.path == "/") {
            return "<html><body><h1>Welcome to the POST "
                   "endpoint</h1></body></html>";
        }
        return "<html><body><h1>404 Not Found</h1></body></html>";
    }
};

class DeleteRequestHandler : public IRequestHandler {
   private:
    std::shared_ptr<Logger> m_logger;

   public:
    DeleteRequestHandler(std::shared_ptr<Logger> logger) : m_logger(logger) {}

    std::string handleRequest(const HttpRequest& request) override {
        LOG_INFO(m_logger, "--- DELETE REQUEST --- \n{}", request.to_string());
        if (request.path == "/") {
            return "<html><body><h1>Welcome to the DELETE "
                   "endpoint</h1></body></html>";
        }
        return "<html><body><h1>404 Not Found</h1></body></html>";
    }
};