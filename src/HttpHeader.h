//
// Created by goforbroke on 02.11.18.
//

#ifndef NATIVE_WEB_APP_HTTPHEADER_H
#define NATIVE_WEB_APP_HTTPHEADER_H


#include <map>
#include <vector>
#include <string>

namespace net {
    namespace http {
        class HttpHeader {
        private:
            std::map<std::string, std::vector<std::string>> headers;
        public:
            void Add(const std::string &key, const std::string &value);

            void Del(const std::string &key);

            std::string Get(const std::string &key);

            void Set(const std::string &key, const std::string &value);
        };
    }
}

#endif //NATIVE_WEB_APP_HTTPHEADER_H
