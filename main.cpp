#include <iostream>
#include <string>
#include <ctime>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/config.hpp>

using tcp = boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
    try {
        if (argc != 3) {
            std::cerr <<
                      "Usage: native-web-app <address> <port> \n" <<
                      "Example:\n" <<
                      "    native-web-app 0.0.0.0 8080 \n";
            return EXIT_FAILURE;
        }
        auto const address = boost::asio::ip::make_address(argv[1]);
        auto const port = static_cast<unsigned short>(std::atoi(argv[2]));


        boost::asio::io_context ioc{1}; // The io_context is required for all I/O
        tcp::acceptor acceptor{ioc, {address, port}}; // The acceptor receives incoming connections

        for (;;) {
            tcp::socket socket{ioc}; // This will receive the new connection
            acceptor.accept(socket); // Block until we get a connection

            time_t now = time(0);
            char* dt = ctime(&now);

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
                    "Cache-Control : no-cache, private\r\n"
                    "Content-Length : %d\r\n"
                    "Date : Mon, 24 Nov 2014 12:03:43 GMT\r\n\r\n",
                    content_length
            );

            boost::asio::write(socket, boost::asio::buffer(buf1, strlen(buf1)));
            boost::asio::write(socket, boost::asio::buffer(buf2, strlen(buf2)));
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}