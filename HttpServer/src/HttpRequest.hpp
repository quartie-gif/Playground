#pragma once

#include <sstream>
#include <string>
#include <unordered_map>

enum class HttpMethod { GET, POST, PUT, DELETE, PATCH, HEAD, OPTIONS, UNKNOWN };

struct HttpRequest {

    HttpMethod method;
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

    std::string to_string() const {
        std::ostringstream os;

        switch (this->method) {
            case HttpMethod::GET:
                os << "GET";
                break;
            case HttpMethod::POST:
                os << "POST";
                break;
            case HttpMethod::PUT:
                os << "PUT";
                break;
            case HttpMethod::DELETE:
                os << "DELETE";
                break;
            case HttpMethod::PATCH:
                os << "PATCH";
                break;
            case HttpMethod::HEAD:
                os << "HEAD";
                break;
            case HttpMethod::OPTIONS:
                os << "OPTIONS";
                break;
            case HttpMethod::UNKNOWN:
                os << "UNKNOWN";
                break;
        }

        os << " " << this->path << " HTTP/1.1\r\n";

        for (const auto& header : this->headers) {
            os << " " << header.first << ": " << header.second << "\r\n";
        }

        os << "\r\n";

        if (!this->body.empty()) {
            os << this->body;
        }

        return os.str();
    }
};