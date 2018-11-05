//
// Created by goforbroke on 26.10.18.
//
#ifndef NET_HTTP_H
#define NET_HTTP_H

#include <map>
#include <string>

#include "net/http/Request.h"

namespace net {
    namespace mux {

        using namespace std;
        using namespace net;

        vector<string> getVarNames(const string &UriPattern);

        vector<string> getVarValues(const string &UriPattern, const string &uri);

        map<string, string> Vars(const http::Request &req);
    }
}

#endif //NET_HTTP_H
