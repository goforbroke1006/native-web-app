//
// Created by goforbroke on 02.11.18.
//

#include "Router.h"
#include "common.h"

using namespace std;

net::http::Router *net::http::Router::Handle(
        const string &path,
        http::RequestHandlerFunc func
) {
    this->routingList.insert(make_pair(path, func));
    return this;
}

net::http::RequestHandlerFunc net::http::Router::resolve(
        const string &path,
        Request &req
) {
    smatch match;
    for (auto const &r : this->routingList) {
        const string &patter = http::getUriRegexPatter(r.first);
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
