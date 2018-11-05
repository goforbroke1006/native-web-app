//
// Created by goforbroke on 02.11.18.
//

#include <iostream>

#include "Server.h"

using namespace net::http;

void Server::processResponse(int new_socket, Router *router) {
    char buffer[BUFFER_SIZE];
    ssize_t valRead = read(new_socket, buffer, BUFFER_SIZE);
    if (0 == valRead) return;

    Request req = parseRequest(buffer);
    RequestHandlerFunc func = router->resolve(req.RequestURI(), req);
    if (nullptr == func) return; // TODO: 404
    auto *w = new ResponseWriter;
    w->WriteHeader(200);
    func(w, req);

    std::string msg = w->flush();
    send(new_socket, msg.c_str(), msg.length(), 0);

    valRead = read(new_socket, buffer, BUFFER_SIZE);
    close(new_socket);
}

Server *net::http::NewServer(
        const std::string &host,
        const unsigned int &port, Router *router
) {
    int server_fd;
    struct sockaddr_in address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw HttpServerException("socket failed");
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
        throw HttpServerException("setsockopt");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = ((in_addr *) (gethostbyname(host.c_str())->h_addr_list[0]))->s_addr;
    address.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0)
        throw HttpServerException("bind failed");
    return new Server(server_fd, address, router);
}

void Server::ListenAndServe() {
    if (listen(server_fd, 3) < 0)
        throw HttpServerException("listen problem");

    int addrlen = sizeof(address);
    int new_socket;
    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
            std::cerr << "accept" << std::endl;
        } else
            std::thread{
                    std::bind(processResponse, new_socket, this->router)
            }.detach();
    }
}
