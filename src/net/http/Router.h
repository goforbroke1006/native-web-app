//
// Created by goforbroke on 02.11.18.
//

#ifndef NATIVE_WEB_APP_ROUTER_H
#define NATIVE_WEB_APP_ROUTER_H


#include <string>
#include <map>
#include <regex>

#include "net/mux/common.h"
#include "ResponseWriter.h"
#include "Request.h"

namespace net {
    namespace http {

        typedef void(*RequestHandlerFunc)(ResponseWriter *, const Request &);

        class Router {
        private:
            std::map<std::string, RequestHandlerFunc> routingList;
        public:
            Router *Handle(const std::string &path, RequestHandlerFunc func);

            RequestHandlerFunc resolve(const std::string &path, Request &req);
        };

        Router *NewServeMux();

    }
}

#endif //NATIVE_WEB_APP_ROUTER_H
