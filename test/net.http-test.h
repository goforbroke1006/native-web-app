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

TEST(net_http_Server_parseRequest, positive3) {
    http::Request req = http::parseRequest(
            "POST /qwertyuiop HTTP/1.1\r\n"
            "Host: foo.com\r\n"
            "Content-Type: application/x-www-form-urlencoded\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "say=Hi&to=Mom"
    );
    ASSERT_EQ(http::RequestMethod::POST, req.Method());
    ASSERT_EQ("/qwertyuiop", req.RequestURI());
    ASSERT_EQ("application/x-www-form-urlencoded", req.Header().Get("Content-Type"));

    req.ParseForm();

    ASSERT_EQ("Hi", req.Form().at("say"));
}



#endif //NET_HTTP_TEST_H
