//
// Created by goforbroke on 02.11.18.
//

#ifndef NATIVE_WEB_APP_RESPONSEWRITER_H
#define NATIVE_WEB_APP_RESPONSEWRITER_H


#include <string>

#include "net/http/HttpHeader.h"

namespace net {
    namespace http {
        using namespace std;

        class ResponseWriter {
        private:
            static const int BUFFER_SIZE = 1024;

            unsigned int statusCode;
            string body;
        public:
            HttpHeader *Header();

            void Write(string &data);

            void WriteHeader(unsigned int statusCode);

            string flush();
        };
    }
}


#endif //NATIVE_WEB_APP_RESPONSEWRITER_H
