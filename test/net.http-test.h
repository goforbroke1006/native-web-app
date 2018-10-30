#ifndef NET_HTTP_TEST_H
#define NET_HTTP_TEST_H

#include <gtest/gtest.h>
#include "../src/net.http.h"

using namespace net;

TEST(net_http_getRequestMethodFromString, positive) {
    http::RequestMethod rm = http::getRequestMethodFromString("GET");
    ASSERT_EQ(http::RequestMethod::GET, rm);
}

TEST(net_http_Server_parseRequest, positive) {
    http::Request req = http::parseRequest(
        "GET /wildfowl HTTP/1.1\r\n"
        "Host: www.wildfowl.org\r\n"
    );
    ASSERT_EQ("/wildfowl", req.RequestURI());
    ASSERT_EQ("www.wildfowl.org", req.Header()->Get("Host"));
}

#endif //NET_HTTP_TEST_H