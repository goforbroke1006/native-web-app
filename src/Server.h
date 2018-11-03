//
// Created by goforbroke on 02.11.18.
//

#ifndef NATIVE_WEB_APP_SERVER_H
#define NATIVE_WEB_APP_SERVER_H

#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <thread>
#include <functional>

#include "Router.h"
#include "HttpServerException.h"

namespace net {
    namespace http {
        class Server {
        private:
            int server_fd;
            struct sockaddr_in address;
            net::http::Router *router;

            Server() = default;

            Server(int serverSocket, sockaddr_in address, net::http::Router *router)
                    : server_fd(serverSocket),
                      address(address),
                      router(router) {}

            static void processResponse(int new_socket, Router *router);

        public:
            friend Server *NewServer(const char *host, const unsigned int &port, Router *router);

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

        Server *NewServer(const char *host, const unsigned int &port, Router *router);
    }
}


#endif //NATIVE_WEB_APP_SERVER_H
