//
// Created by goforbroke on 05.11.18.
//

#ifndef NATIVE_WEB_APP_COMMON_H
#define NATIVE_WEB_APP_COMMON_H

#include <string>
#include <regex>

namespace net {

    using namespace std;

    string getUriRegexPatter(const string &rawPattern);

    vector<string> getVarNames(const string &UriPattern);

    vector<string> getVarValues(const string &UriPattern, const string &uri);

}

#endif //NATIVE_WEB_APP_COMMON_H
