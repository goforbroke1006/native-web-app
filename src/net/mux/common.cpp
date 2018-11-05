//
// Created by goforbroke on 05.11.18.
//

#include "common.h"

using namespace std;
using namespace net;

map <string, string> net::mux::Vars(const http::Request &req) {

    map<string, string> vars;

    vector<string> names = getVarNames(*req.getUriPattern());
    vector<string> values = getVarValues(*req.getUriPattern(), req.RequestURI());

    for (int i = 0; i < names.size(); ++i) {
        vars.insert(make_pair(names[i], values[i]));
    }

    return vars;
}
