//
// Created by goforbroke on 02.11.18.
//

#ifndef NATIVE_WEB_APP_HTTPSERVEREXCEPTION_H
#define NATIVE_WEB_APP_HTTPSERVEREXCEPTION_H

#include <string>
#include <exception>


namespace net {
    namespace http {
        class HttpServerException : public std::exception {
        private:
            std::string message;
        public:
            explicit HttpServerException(std::string message)
                    : message(std::move(message)) {}

            const char *what() const throw() override {
                return message.c_str();
            }

            virtual ~HttpServerException() throw() {}
        };
    }
}

#endif //NATIVE_WEB_APP_HTTPSERVEREXCEPTION_H
