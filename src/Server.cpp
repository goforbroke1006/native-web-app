//
// Created by goforbroke on 02.11.18.
//

#include "Server.h"

using namespace net::http;

void Server::processResponse(int new_socket, Router *router) {
    size_t bs = 2048;
    char buffer[bs];
    ssize_t valread = read(new_socket, buffer, bs);

    if (0 == valread) return;

//                std::cout << "Request: " << std::endl;
//                std::cout << buffer << std::endl;

    Request req = parseRequest(buffer);
    requestHandler func = router->resolve(req.RequestURI());
    if (nullptr == func)
        return; // TODO: throw 404 exception
    auto *w = new ResponseWriter;
    func(w, req);

    std::string msg = w->flush();
    send(new_socket, msg.c_str(), msg.length(), 0);

    valread = read(new_socket, buffer, bs);
    close(new_socket);
}

Server *net::http::NewServer(const std::string &host, const unsigned int &port, Router *router) {
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
    address.sin_addr.s_addr = ((in_addr *) (gethostbyname(host.c_str())->h_addr_list[0]))->s_addr;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        throw HttpServerException("bind failed");
    }

    return new Server(server_fd, address, router);
}
