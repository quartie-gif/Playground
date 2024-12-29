#pragma once

#include <string>
#include "HttpRequest.hpp"

class IRequestHandler {
   public:
    virtual ~IRequestHandler() = default;
    virtual std::string handleRequest(const HttpRequest& request) = 0;
};