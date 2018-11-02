//
// Created by goforbroke on 02.11.18.
//

#include "HttpHeader.h"

using namespace net::http;

void HttpHeader::Add(const std::string &key, const std::string &value) {
    if (headers.find(key) == headers.end()) {
        std::vector<std::string> vals;
        headers.insert(std::make_pair(key, vals));
    }
    headers.at(key).push_back(value);
}

void HttpHeader::Del(const std::string &key) {
    headers.erase(key);
}

std::string HttpHeader::Get(const std::string &key) {
    if (headers.find(key) == headers.end()) {
        return "";
    }
    return headers.at(key).front();
}

void HttpHeader::Set(const std::string &key, const std::string &value) {
    std::vector<std::string> vals;
    headers.insert(std::make_pair(key, vals));
    headers.at(key).push_back(value);
}