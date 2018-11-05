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
#include <net/mux/common.h>

#include "net/http/Router.h"
#include "net/http/Server.h"

using namespace std;
using namespace net;

void indexHandler(http::ResponseWriter *resp, const http::Request &req) {
    string content = "Index page";
    resp->Write(content);
}

void greetingHandler(http::ResponseWriter *resp, const http::Request &req) {
    const map<string, string> &vars = mux::Vars(req);
    string content = "Hello, " + vars.at("name") + "!";
    resp->Write(content);
}

void greetAndMessageHandler(http::ResponseWriter *resp, const http::Request &req) {
    const map<string, string> &vars = mux::Vars(req);
    string content = "Hello, " + vars.at("name") + "!";
    content += "<br/>";
    content += "Message: " + vars.at("message");
    resp->Write(content);
}

int handle(string &host, unsigned int port) {
    try {
        auto *router = http::NewServeMux();
        router
                ->Handle("/", indexHandler)
                ->Handle("/hello/{name}", greetingHandler)
                ->Handle("/hello/{name}/{message}", greetAndMessageHandler);
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

    string host = argv[1];
    auto port = static_cast<unsigned int>(strtol(argv[2], nullptr, 10));

    handle(host, port);

    return 0;
}
