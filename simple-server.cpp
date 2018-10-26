//
// Created by goforbroke on 26.10.18.
//

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

void processResponse(int new_socket) {
    std::cout << "Request to: " << new_socket << std::endl;

    time_t now = time(0);
    char *dt = ctime(&now);

    char buf1[1024];
    char buf2[1024];
    sprintf(buf2, "<html>"
                  "<head>"
                  "<title>Hello, World!</title>"
                  "</head>"
                  "<body>"
                  "    TIME : %d <br>"
                  "    DATE: %s"
                  "</body>"
                  "</html>",
            now,
            dt
    );

    size_t content_length = strlen(buf2);
    sprintf(
            buf1,

            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            "Server: Wildfowl\r\n"
            "X-AspNet-Version: 2.0.50727\r\n"
            "X-Powered-By: GFB\r\n"
            "Connection: close\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %d\r\n"
            "Cache-Control : no-cache, private\r\n"
            "Date : %s\r\n",
            content_length,
            dt
    );

    std::string msg;
    msg += buf1;
    msg += buf2;

    send(new_socket, msg.c_str(), msg.length(), 0);

    std::cout << "send response" << std::endl;

    char buffer[2014];
    size_t valread = read( new_socket , buffer, 1024);

    close(new_socket);
}

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

    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = ((in_addr *) (gethostbyname(host)->h_addr_list[0]))->s_addr;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int new_socket;
    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
            perror("accept");
            continue;
        }
        std::thread{
                std::bind(processResponse, new_socket)
        }.detach();
    }
    return 0;
}