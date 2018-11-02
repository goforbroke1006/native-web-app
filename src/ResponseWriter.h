//
// Created by goforbroke on 02.11.18.
//

#ifndef NATIVE_WEB_APP_RESPONSEWRITER_H
#define NATIVE_WEB_APP_RESPONSEWRITER_H


#include <string>
#include "HttpHeader.h"

namespace net {
    namespace http {
        class ResponseWriter {
        private:
            unsigned int statusCode;
            std::string body;
        public:
            HttpHeader *Header();

            void Write(std::string data);

            void WriteHeader(unsigned int statusCode);

            std::string flush();
        };
    }
}


#endif //NATIVE_WEB_APP_RESPONSEWRITER_H
