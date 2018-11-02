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
            Request();

            Request(
                    RequestMethod method,
                    std::string &path,
                    http::HttpHeader *header
            ) : method(method),
                path(std::move(path)),
                header(header) {}

            HttpHeader *Header();

            RequestMethod Method();

            std::string RequestURI();

            void setMethod(RequestMethod method);

            void setPath(const std::string &path);

            void setHeader(http::HttpHeader *header);
        };

        RequestMethod getRequestMethodFromString(const std::string &val) {
            if ("GET" == val) return RequestMethod::GET;
            if ("POST" == val) return RequestMethod::POST;
            if ("PUT" == val) return RequestMethod::PUT;
            if ("DELETE" == val) return RequestMethod::DELETE;
            if ("HEAD" == val) return RequestMethod::HEAD;
        }

        Request parseRequest(const std::string &raw) {
            Request request;

            std::istringstream f(raw);

            std::string statusLine;
            std::getline(f, statusLine);

            {
                std::string s;
                std::istringstream issStatus(statusLine);

                getline(issStatus, s, ' ');
                request.setMethod(getRequestMethodFromString(s));

                getline(issStatus, s, ' ');
                request.setPath(s);
            }

            std::string headerLine;
            while (std::getline(f, headerLine)) {
                headerLine = headerLine.substr(0, headerLine.length() - 1);

                unsigned long delimiterPos = headerLine.find(':');
                const std::string &name = headerLine.substr(0, delimiterPos);
                std::string values = headerLine.substr(delimiterPos + 1);
                if (" " == values.substr(0, 1)) {
                    values = values.substr(1);
                }

                std::string valLine;
                std::istringstream issHeaderVals(values);
                while (std::getline(issHeaderVals, valLine, ',')) {
                    request.Header()->Add(name, valLine);
                }
            }
            return request;
        }

    }
}


#endif //NATIVE_WEB_APP_REQUEST_H
