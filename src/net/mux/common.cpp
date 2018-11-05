//
// Created by goforbroke on 05.11.18.
//

#include "net/http/common.h"

#include "common.h"

using namespace std;
using namespace net;

vector <string> mux::getVarNames(const string &UriPattern) {
    vector<string> names;

    regex exp(R"([\{]{1}([\w]+)[\}]{1})");
    string::const_iterator searchStart = UriPattern.cbegin();
    smatch res;
    while (regex_search(searchStart, UriPattern.cend(), res, exp)) {
        searchStart += res.position() + res.length();
        names.emplace_back(res[1].str());
    }

    return names;
}

vector<string> net::mux::getVarValues(const string &UriPattern, const string &uri) {
    vector<string> values;

    const string &patter = http::getUriRegexPatter(UriPattern);
    smatch match;
    if (regex_match(uri, match, regex(patter))) {
        for (auto &m : match) {
            if (m == match[0]) continue;
            const string &v = m.str().c_str();
            values.push_back(v);
        }
    }

    return values;
}

map <string, string> net::mux::Vars(const http::Request &req) {

    map<string, string> vars;

    vector<string> names = getVarNames(*req.getUriPattern());
    vector<string> values = getVarValues(*req.getUriPattern(), req.RequestURI());

    for (int i = 0; i < names.size(); ++i) {
        vars.insert(make_pair(names[i], values[i]));
    }

    return vars;
}
