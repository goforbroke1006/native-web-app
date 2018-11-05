//
// Created by goforbroke on 05.11.18.
//

#include "common.h"

using namespace std;
using namespace net;

string http::getUriRegexPatter(const string &rawPattern) {
    const regex re(R"([\{]{1}[\w]+[\}]{1})");
    const string &replacement = string(R"(([\w]+))");
    return regex_replace(rawPattern, re, replacement);
}
