#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <functional>
#include <thread>
#include "net.http.h"

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cerr <<
                  "Usage: native-web-app <address> <port> \n" <<
                  "Example:\n" <<
                  "    native-web-app 0.0.0.0 8080 \n";
        return EXIT_FAILURE;
    }

    const char *host = argv[1];
    int port = std::atoi(argv[2]);

    using namespace net;

    auto *router = http::NewRouter();

    router
            ->Handle("/", [](const http::ResponseWriter *resp, const http::Request req) {
                // TODO: implement me
            })
            ->Handle("/hello/{name}", [](const http::ResponseWriter *resp, const http::Request req) {
                // TODO: implement me
            });

    auto *server = http::NewServer(host, port, router);

    server->ListenAndServe();

    return 0;
}
