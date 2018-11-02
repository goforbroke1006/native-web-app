//
// Created by goforbroke on 02.11.18.
//

#include "ResponseWriter.h"

net::http::HttpHeader *net::http::ResponseWriter::Header() { return nullptr; }

void net::http::ResponseWriter::Write(std::string data) {
    body = data;
}

void net::http::ResponseWriter::WriteHeader(unsigned int statusCode) { this->statusCode = statusCode; }

std::string net::http::ResponseWriter::flush() {
    time_t timer = time(0);
    char *dt = ctime(&timer);

    char buf1[1024];
    sprintf(
            buf1,
            "HTTP/1.1 %d OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            "Server: Wildfowl\r\n"
            "X-Powered-By: GFB\r\n"
            "Connection: close\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %zu\r\n"
            "Cache-Control : no-cache, private\r\n"
            "Date : %s\r\n",
            this->statusCode,
            this->body.length(),
            dt
    );

    std::string rawData = "";
    rawData += buf1;
    rawData += this->body;

    return rawData;
}
