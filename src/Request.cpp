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

RequestMethod net::http::getRequestMethodFromString(const std::string &val) {
    if ("GET" == val) return RequestMethod::GET;
    if ("POST" == val) return RequestMethod::POST;
    if ("PUT" == val) return RequestMethod::PUT;
    if ("DELETE" == val) return RequestMethod::DELETE;
    if ("HEAD" == val) return RequestMethod::HEAD;
}

Request net::http::parseRequest(const std::string &raw) {
    Request request;


    std::istringstream f(raw);

    std::string statusLine;
    std::getline(f, statusLine);

    {
        std::string s;
        std::istringstream issStatus(statusLine);

        getline(issStatus, s, ' ');
        request.setMethod(getRequestMethodFromString(s));

        getline(issStatus, s, ' ');
        request.setPath(s);
    }

    std::string headerLine;
    while (std::getline(f, headerLine)) {
        headerLine = headerLine.substr(0, headerLine.length() - 1);

        unsigned long delimiterPos = headerLine.find(':');
        const std::string &name = headerLine.substr(0, delimiterPos);
        std::string values = headerLine.substr(delimiterPos + 1);
        if (" " == values.substr(0, 1)) {
            values = values.substr(1);
        }

        std::string valLine;
        std::istringstream issHeaderVals(values);
        while (std::getline(issHeaderVals, valLine, ',')) {
            request.Header()->Add(name, valLine);
        }
    }
    return request;
}
