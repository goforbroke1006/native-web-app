//
// Created by goforbroke on 05.11.18.
//

#ifndef NATIVE_WEB_APP_COMMON_H
#define NATIVE_WEB_APP_COMMON_H

#include <string>
#include <regex>

namespace net {
namespace http {

    using namespace std;

    string getUriRegexPatter(const string &rawPattern);



}
}

#endif //NATIVE_WEB_APP_COMMON_H
