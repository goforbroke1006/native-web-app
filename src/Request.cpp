//
// Created by goforbroke on 02.11.18.
//

#include "Request.h"

using namespace net::http;

Request::Request() {
    header = new HttpHeader;
}

HttpHeader *Request::Header() {
    return header;
}

RequestMethod Request::Method() {
    return method;
}

std::string Request::RequestURI() {
    return path;
}

void Request::setMethod(net::http::RequestMethod method) {
    this->method = method;
}

void Request::setPath(const std::string &path) {
    this->path = path;
}

void Request::setHeader(net::http::HttpHeader *header) {
    this->header = header;
}
