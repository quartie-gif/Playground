#pragma once

#include <iostream>
#include <memory>
#include <string_view>
#include <vector>

#include <Logger/Logger.hpp>
#include "HttpRequest.hpp"
#include "IHttpRequestParser.hpp"

class HttpRequestParser : public IHttpRequestParser {
   public:
    HttpRequestParser(std::shared_ptr<Logger> logger) : m_logger(logger) {}

    HttpRequest parseRequest(const std::string& raw_request) const override {
        LOG_DEBUG(m_logger, "Raw request: {}", raw_request);
        HttpRequest request;
        std::istringstream request_stream(raw_request);
        std::string line;

        std::getline(request_stream, line);
        parseRequestLine(line, request);

        while (std::getline(request_stream, line) && !line.empty()) {
            parseHeader(line, request);
        }

        if (request_stream.peek() != EOF) {
            request.body.assign(std::istreambuf_iterator<char>(request_stream),
                                std::istreambuf_iterator<char>());
        }

        return request;
    }

   private:
    std::shared_ptr<Logger> m_logger;

    void parseRequestLine(const std::string& line, HttpRequest& request) const {
        std::istringstream line_stream(line);
        std::string method_str;
        line_stream >> method_str >> request.path;

        request.method = stringToHttpMethod(method_str);
    }

    void parseHeader(const std::string& line, HttpRequest& request) const {
        size_t delimiter_pos = line.find(':');
        if (delimiter_pos != std::string::npos) {
            std::string header_name = line.substr(0, delimiter_pos);
            std::string header_value = line.substr(delimiter_pos + 1);

            header_value.erase(0, header_value.find_first_not_of(" \t"));
            request.headers[header_name] = header_value;
        }
    }

    HttpMethod stringToHttpMethod(const std::string& method_str) const {
        if (method_str == "GET")
            return HttpMethod::GET;
        if (method_str == "POST")
            return HttpMethod::POST;
        if (method_str == "PUT")
            return HttpMethod::PUT;
        if (method_str == "DELETE")
            return HttpMethod::DELETE;
        if (method_str == "PATCH")
            return HttpMethod::PATCH;
        if (method_str == "HEAD")
            return HttpMethod::HEAD;
        if (method_str == "OPTIONS")
            return HttpMethod::OPTIONS;
        return HttpMethod::UNKNOWN;
    }
};
