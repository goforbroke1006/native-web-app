//
// Created by goforbroke on 02.11.18.
//

#include "Router.h"

net::http::Router *net::http::Router::Handle(const char *path, net::http::requestHandler rh) {
    this->routings.insert(std::make_pair(path, rh));
    return this;
}

std::string net::http::Router::getUriRegexPatter(std::string rawPattern) {
    const std::regex re("[\\{]{1}[\\w]+[\\}]{1}");
    return regex_replace(rawPattern, re, std::string("([\\w]+)"));
}

net::http::requestHandler net::http::Router::resolve(const std::string &path) {
    std::smatch match;
    for (auto const &r : this->routings) {
        const std::string &patter = getUriRegexPatter(r.first);
        const std::regex re(patter);
        if (std::regex_match(path, match, re)) {
            return r.second;
        }
    }
    return nullptr;
}

net::http::Router *net::http::NewServeMux() {
    return new Router;
}
