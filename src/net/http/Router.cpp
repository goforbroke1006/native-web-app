//
// Created by goforbroke on 02.11.18.
//

#include "Router.h"

using namespace std;

//std::string net::http::getUriRegexPatter(string rawPattern) {
//    const regex re(R"([\{]{1}[\w]+[\}]{1})");
//    const string &replacement = string(R"(([\w]+))");
//    return regex_replace(rawPattern, re, replacement);
//}

net::http::Router *net::http::Router::Handle(
        const string &path,
        http::RequestHandlerFunc func
) {
    this->routingList.insert(make_pair(path, func));
    return this;
}

//std::string net::http::Router::getUriRegexPatter(string rawPattern) {
//    const regex re(R"([\{]{1}[\w]+[\}]{1})");
//    const string &replacement = string(R"(([\w]+))");
//    return regex_replace(rawPattern, re, replacement);
//}

net::http::RequestHandlerFunc net::http::Router::resolve(
        const string &path,
        Request &req
) {
    smatch match;
    for (auto const &r : this->routingList) {
        const string &patter = getUriRegexPatter(r.first);
        const regex re(patter);
        if (regex_match(path, match, re)) {
            req.setUriPattern(new string(r.first));
            return r.second;
        }
    }
    return nullptr;
}

net::http::Router *net::http::NewServeMux() {
    return new Router;
}
