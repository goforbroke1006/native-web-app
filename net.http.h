//
// Created by goforbroke on 26.10.18.
//

#ifndef NET_HTTP_H
#define NET_HTTP_H

#include <map>
#include <functional>

namespace net {
    namespace http {
        class Header {
        private:
            std::map<std::string>
        public:
            void Add(std::string key, std::string value) { /**/ }

            void Del(std::string key) { /**/ }

            std::string Get(std::string key) { /**/ }

            void Set(std::string key, std::string value) { /**/ }
        };

        class Request {
        };

        class ResponseWriter {
        public:
            Header *Header() { return nullptr; }
        };

        class Router {
        public:
            Router *Handle(const char *path, void(*h)(const ResponseWriter *, const Request)) {
                // TODO: implement me!
                return this;
            }
        };

        Router *NewRouter() {
            return new Router;
        }

        class Server {
        private:
            Server() = default;

            Server(const char *host, const int &port, Router *router) {}

            friend Server *NewServer(const char *host, const int &port, Router *router);

        public:
            void ListenAndServe() {
                // TODO: implement me!
            }
        };

        Server *NewServer(const char *host, const int &port, Router *router) {
            // TODO: check port free
            return new Server(host, port, router);
        }
    }
}

#endif //NET_HTTP_H
