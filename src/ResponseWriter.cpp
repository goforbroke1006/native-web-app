//
// Created by goforbroke on 02.11.18.
//

#include "ResponseWriter.h"

net::http::HttpHeader *net::http::ResponseWriter::Header() { return nullptr; }

void net::http::ResponseWriter::Write(std::string &data) {
    body = data;
}

void net::http::ResponseWriter::WriteHeader(unsigned int statusCode) { this->statusCode = statusCode; }

std::string net::http::ResponseWriter::flush() {
    char buf1[BUFFER_SIZE];
    sprintf(
            buf1,
            "HTTP/1.1 %d OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            "Connection: close\r\n"
            "Content-Length: %zu\r\n",
            this->statusCode,
            this->body.length()
    );

    std::string rawData;
    rawData += buf1;
    rawData += this->body;

    return rawData;
}
