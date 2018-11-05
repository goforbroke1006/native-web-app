//
// Created by goforbroke on 05.11.18.
//

#include "common.h"

using namespace std;

string net::getUriRegexPatter(const string &rawPattern) {
    const regex re(R"([\{]{1}[\w]+[\}]{1})");
    const string &replacement = string(R"(([\w]+))");
    return regex_replace(rawPattern, re, replacement);
}

vector <string> net::getVarNames(const string &UriPattern) {
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

vector<string> net::getVarValues(const string &UriPattern, const string &uri) {
    vector<string> values;

    const string &patter = getUriRegexPatter(UriPattern);
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
