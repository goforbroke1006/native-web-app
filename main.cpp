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

#include "src/Router.h"
#include "src/Server.h"

using namespace net;

void indexHandler(http::ResponseWriter *resp, const http::Request &req) {
    std::string content = "Index page";
    resp->Write(content);
}

void greatingHandler(http::ResponseWriter *resp, const http::Request &req) {
    std::string content = "Hello, Petya!";
    resp->Write(content);
}

int handle(std::string &host, unsigned int port) {
    try {
        auto *router = http::NewServeMux();
        router
                ->Handle("/", indexHandler)
                ->Handle("/hello/{name}", greatingHandler);
        auto *server = http::NewServer(host, port, router);
        server->ListenAndServe();
    } catch (http::HttpServerException &ex) {
        std::cerr << ex.what();
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cerr <<
                  "Usage: native-web-app <address> <port> \n" <<
                  "Example:\n" <<
                  "    native-web-app 0.0.0.0 8080 \n";
        return EXIT_FAILURE;
    }

    std::string host = argv[1];
    auto port = static_cast<unsigned int>(std::strtol(argv[2], nullptr, 10));

    handle(host, port);

    return 0;
}
