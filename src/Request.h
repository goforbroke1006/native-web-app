//
// Created by goforbroke on 02.11.18.
//

#ifndef NATIVE_WEB_APP_REQUEST_H
#define NATIVE_WEB_APP_REQUEST_H

#include <sstream>
#include "HttpHeader.h"

namespace net {
    namespace http {

        enum RequestMethod {
            GET, POST, PUT, DELETE, HEAD
        };

        class Request {
        private:
            RequestMethod method;
            std::string path;
            HttpHeader *header;

        public:
            explicit Request() noexcept;

            Request(
                    RequestMethod method,
                    std::string &path,
                    http::HttpHeader *header
            ) noexcept
                    : method(method),
                      path(std::move(path)),
                      header(header) {}

            HttpHeader *Header();

            RequestMethod Method();

            std::string RequestURI();

            void setMethod(RequestMethod method);

            void setPath(const std::string &path);

            void setHeader(http::HttpHeader *header);

            static RequestMethod getRequestMethodFromString(const std::string &val);

            static void parseHttpStatusLine(Request &request, std::istringstream &f);

            static void parseHeaderLine(Request &request, const std::string &headerLine);

            static void parseHttpHeadersLines(Request &request, std::istringstream &f);
        };

        Request parseRequest(const std::string &raw);

    }
}


#endif //NATIVE_WEB_APP_REQUEST_H
