//
// Created by goforbroke on 02.11.18.
//

#ifndef NATIVE_WEB_APP_SERVER_H
#define NATIVE_WEB_APP_SERVER_H

#include <cstddef>

static const size_t BUFFER_SIZE = 2048;

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
            friend Server *NewServer(const std::string &host, const unsigned int &port, Router *router);

            void ListenAndServe();
        };

        Server *NewServer(const std::string &host, const unsigned int &port, Router *router);
    }
}


#endif //NATIVE_WEB_APP_SERVER_H
