#include <utility>

//
// Created by goforbroke on 26.10.18.
//

#ifndef NET_HTTP_H
#define NET_HTTP_H

#include <map>
#include <vector>
#include <functional>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <exception>
#include <sstream>
#include <thread>

namespace net {
    namespace http {

        class HttpServerException : public std::exception {
        private:
            std::string message;
        public:
            HttpServerException(const std::string &message) : message(message) {}

            const char *what() const throw() override {
                return message.c_str();
            }

            virtual ~HttpServerException() throw() {}
        };

        class HttpHeader {
        private:
            std::map<std::string, std::vector<std::string>> headers;
        public:
            void Add(const std::string key, const std::string &value) {
                if (headers.find(key) == headers.end()) {
                    std::vector<std::string> vals;
                    headers.insert(std::make_pair(key, vals));
                }
                headers.at(key).push_back(value);
            }

            void Del(const std::string &key) {
                headers.erase(key);
            }

            std::string Get(const std::string &key) {
                if (headers.find(key) == headers.end()) {
                    return "";
                }
                return headers.at(key).front();
            }

            void Set(const std::string &key, const std::string &value) {
                std::vector<std::string> vals;
                headers.insert(std::make_pair(key, vals));
                headers.at(key).push_back(value);
            }
        };

        enum RequestMethod {
            GET, POST, PUT, DELETE, HEAD
        };

        RequestMethod getRequestMethodFromString(const std::string &val) {
            if ("GET" == val) return RequestMethod::GET;
            if ("POST" == val) return RequestMethod::POST;
            if ("PUT" == val) return RequestMethod::PUT;
            if ("DELETE" == val) return RequestMethod::DELETE;
            if ("HEAD" == val) return RequestMethod::HEAD;
        }

        class Request {
        private:
            RequestMethod method;
            std::string path;
            HttpHeader *header;
        public:
            Request() {
                header = new HttpHeader;
            }

            Request(
                    RequestMethod method,
                    std::string &path,
                    http::HttpHeader *header
            )
                    : method(method),
                      path(std::move(path)),
                      header(header) {}

            HttpHeader *Header() {
                return header;
            }

            RequestMethod Method() {
                return method;
            }

            std::string RequestURI() {
                return path;
            }

            void setMethod(RequestMethod method) {
                Request::method = method;
            }

            void setPath(const std::string &path) {
                Request::path = path;
            }

            void setHeader(http::HttpHeader *header) {
                Request::header = header;
            }
        };

        class ResponseWriter {
        private:
            unsigned int statusCode;
            std::string body;
        public:
            HttpHeader *Header() { return nullptr; }

            void Write(std::string data) {
                body = data;
            }

            void WriteHeader(unsigned int statusCode) { this->statusCode = statusCode; }

            std::string flush() {
                time_t timer = time(0);
                char *dt = ctime(&timer);

                char buf1[1024];
                sprintf(
                        buf1,
                        "HTTP/1.1 %d OK\r\n"
                        "Content-Type: text/html; charset=utf-8\r\n"
                        "Server: Wildfowl\r\n"
                        "X-Powered-By: GFB\r\n"
                        "Connection: close\r\n"
                        "Content-Type: text/html\r\n"
                        "Content-Length: %d\r\n"
                        "Cache-Control : no-cache, private\r\n"
                        "Date : %s\r\n",
                        this->statusCode,
                        this->body.length(),
                        dt
                );

                std::string rawData = "";
                rawData += buf1;
                rawData += this->body;

                return rawData;
            }
        };

        typedef void(*requestHandler)(ResponseWriter *, const Request);

        class Router {
        private:
            std::map<std::string, requestHandler> routings;
        public:
            Router *Handle(const char *path, requestHandler rh) {
                this->routings.insert(std::make_pair(path, rh));
                return this;
            }

            requestHandler resolve(const std::string &path) {
                for (auto const &r : this->routings) {
                    if (r.first == path) { // TODO: match with regex
                        return r.second;
                    }
                }
                return nullptr;
            }
        };

        Router *NewServeMux() {
            return new Router;
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

        class Server {
        private:
            int server_fd;
            struct sockaddr_in address;
            Router *router;

            Server() = default;

            Server(int serverSocket, sockaddr_in address, Router *router)
                    : server_fd(serverSocket),
                      address(address),
                      router(router) {}

            friend Server *NewServer(const char *host, const unsigned int &port, Router *router);

            static void processResponse(int new_socket, Router *router) {
                size_t bs = 2048;
                char buffer[bs];
                ssize_t valread = read(new_socket, buffer, bs);

                if (0 == valread) return;

                std::cout << "Request: " << std::endl;
                std::cout << buffer << std::endl;

                Request req = parseRequest(buffer);
                requestHandler func = router->resolve(req.RequestURI());
                if (nullptr == func)
                    return; // TODO: throw 404 exception
                ResponseWriter *w = new ResponseWriter;
                func(w, req);

                std::string msg = w->flush();
                send(new_socket, msg.c_str(), msg.length(), 0);

                valread = read(new_socket, buffer, bs);
                close(new_socket);
            }

        public:
            void ListenAndServe() {
                if (listen(server_fd, 3) < 0) {
                    throw HttpServerException("listen problem");
                }

                int addrlen = sizeof(address);
                int new_socket;
                while (true) {
                    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                        perror("accept");
                        continue;
                    }
                    std::thread{
                            std::bind(processResponse, new_socket, this->router)
                    }.detach();
                }
            }
        };

        Server *NewServer(const char *host, const unsigned int &port, Router *router) {
            int server_fd;
            struct sockaddr_in address;

            if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
                throw HttpServerException("socket failed");
            }
            int opt = 1;
            if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
                throw HttpServerException("setsockopt");
            }
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = ((in_addr *) (gethostbyname(host)->h_addr_list[0]))->s_addr;
            address.sin_port = htons(port);

            if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
                throw HttpServerException("bind failed");
            }

            return new Server(server_fd, address, router);
        }
    }
}

#endif //NET_HTTP_H
