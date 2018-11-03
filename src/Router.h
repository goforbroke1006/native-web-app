//
// Created by goforbroke on 02.11.18.
//

#ifndef NATIVE_WEB_APP_ROUTER_H
#define NATIVE_WEB_APP_ROUTER_H


#include <string>
#include <map>
#include <regex>

#include "Request.h"
#include "ResponseWriter.h"

namespace net {
    namespace http {

        typedef void(*requestHandler)(ResponseWriter *, const Request &);

        class Router {
        private:
            std::map<std::string, requestHandler> routings;
        public:
            Router *Handle(const char *path, requestHandler rh);

            static std::string getUriRegexPatter(std::string rawPattern);

            requestHandler resolve(const std::string &path);
        };

        Router *NewServeMux();

    }
}

#endif //NATIVE_WEB_APP_ROUTER_H
