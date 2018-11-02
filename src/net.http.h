#include <utility>

//
// Created by goforbroke on 26.10.18.
//
#ifndef NET_HTTP_H
#define NET_HTTP_H

#include <map>
#include <utility>
#include <vector>
#include <functional>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <exception>
#include <sstream>
#include <thread>
#include <regex>

#include "Request.h"
#include "ResponseWriter.h"
#include "Router.h"
#include "HttpServerException.h"
#include "Server.h"

namespace net {
    namespace mux {
        std::map<std::string, std::string> Vars(net::http::Request &req) {

        }
    }
}

#endif //NET_HTTP_H
