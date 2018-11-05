//
// Created by goforbroke on 05.11.18.
//

#ifndef NATIVE_WEB_APP_NET_MUX_TEST_H
#define NATIVE_WEB_APP_NET_MUX_TEST_H

#include <gtest/gtest.h>

#include "net/mux/common.h"
#include "net/http/Request.h"

using namespace net;
using namespace std;

TEST(net_mux__Vars, positive1) {
    http::Request request;
    request.setPath("/hello/Petya");
    request.setUriPattern(new string("/hello/{name}"));
    map<string, string> actual = mux::Vars(request);
    ASSERT_EQ("Petya", actual.at("name"));
}

TEST(net_mux__Vars, positive2) {
    http::Request request;
    request.setPath("/hello/Petya/HowAreYou");
    request.setUriPattern(new string("/hello/{name}/{message}"));
    map<string, string> actual = mux::Vars(request);
    ASSERT_NE(actual.end(), actual.find("name"));
    ASSERT_NE(actual.end(), actual.find("message"));
    ASSERT_EQ(actual.end(), actual.find("wildfowl"));
}

#endif //NATIVE_WEB_APP_NET_MUX_TEST_H
