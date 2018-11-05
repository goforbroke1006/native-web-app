//
// Created by goforbroke on 02.11.18.
//

#ifndef NATIVE_WEB_APP_REQUEST_H
#define NATIVE_WEB_APP_REQUEST_H


#include <utility>
#include <sstream>

#include "net/http/HttpHeader.h"

namespace net {
    namespace http {

        using namespace std;

        static const char *const DEFAULT_URI = "/";

        enum RequestMethod {
            GET, POST, PUT, DELETE, HEAD
        };

        class Request {
        private:
            RequestMethod method;
            string path;
            HttpHeader header;
            string *uriPattern;
        public:
            explicit Request() noexcept;

            Request(
                    RequestMethod method,
                    std::string path,
                    HttpHeader header
            ) noexcept
                    : method(method),
                      path(std::move(path)),
                      header(std::move(header)) {}

            RequestMethod Method() const;

            const string &RequestURI() const;

            HttpHeader &Header();

            void setMethod(const RequestMethod &method);

            void setPath(const string &path);

            string *getUriPattern() const;

            void setUriPattern(string *uriPattern);

            static RequestMethod getRequestMethodFromString(const string &val);

            static void parseHttpStatusLine(Request &request, istringstream &f);

            static void parseHeaderLine(Request &request, const string &headerLine);

            static void parseHttpHeadersLines(Request &request, istringstream &f);
        };

        Request parseRequest(const string &raw);

    }
}


#endif //NATIVE_WEB_APP_REQUEST_H
