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
        using namespace std;

        class HttpHeader {
        private:
            map<string, vector<string>> headers;
        public:
            void Add(const string &key, const string &value);

            void Del(const string &key);

            string Get(const string &key);

            void Set(const string &key, const string &value);
        };
    }
}

#endif //NATIVE_WEB_APP_HTTPHEADER_H
