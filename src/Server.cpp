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
