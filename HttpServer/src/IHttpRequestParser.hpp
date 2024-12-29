#pragma once

#include <Logger/Logger.hpp>
#include "HttpRequest.hpp"

class IHttpRequestParser {
   public:
    virtual ~IHttpRequestParser() = default;
    virtual HttpRequest parseRequest(const std::string& rawRequest) const = 0;
};