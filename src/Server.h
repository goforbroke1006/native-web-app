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

            friend Server *NewServer(const char *host, const unsigned int &port, Router *router);

            static void processResponse(int new_socket, Router *router);

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


#endif //NATIVE_WEB_APP_SERVER_H
