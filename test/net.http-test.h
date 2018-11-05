#ifndef NET_HTTP_TEST_H
#define NET_HTTP_TEST_H

#include <gtest/gtest.h>

#include "net/http/common.h"
#include "net/http/Request.h"

using namespace net;

TEST(net_http_getRequestMethodFromString, positive) {
    http::RequestMethod rm = http::Request::getRequestMethodFromString("GET");
    ASSERT_EQ(http::RequestMethod::GET, rm);
}

TEST(net_http_Server_parseRequest, positive) {
    http::Request req = http::parseRequest(
        "GET /wildfowl HTTP/1.1\r\n"
        "Host: www.wildfowl.org\r\n"
    );
    ASSERT_EQ("/wildfowl", req.RequestURI());
    ASSERT_EQ("www.wildfowl.org", req.Header().Get("Host"));
}

TEST(net_http_Router__getUriRegexPatter, positive) {
    ASSERT_EQ("/some/fantastic/([\\w]+)/profile", http::getUriRegexPatter("/some/fantastic/{username}/profile"));
    ASSERT_EQ("/", http::getUriRegexPatter("/"));
    ASSERT_EQ("/some/url/id-([\\w]+)", http::getUriRegexPatter("/some/url/id-{someId}"));

//    ASSERT_EQ("/some/url/id-([\\d+])", http::getUriRegexPatter("/some/url/id-{someId:\\d+}")); // TODO: realize it
}



#endif //NET_HTTP_TEST_H
