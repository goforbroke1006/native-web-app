//
// Created by goforbroke on 02.11.18.
//

#include "Request.h"
#include "net/http/HttpServerException.h"

using namespace std;
using namespace net::http;

Request::Request() noexcept {
    method = RequestMethod::GET;
    path = DEFAULT_URI;
    header = HttpHeader();
}

RequestMethod Request::Method() const {
    return method;
}

const string &Request::RequestURI() const {
    return path;
}

HttpHeader &Request::Header() {
    return header;
}

void Request::ParseForm() {
    // TODO:
}

map<string, string> Request::Form() {
    map<string, string> form;
    // TODO: realize parameters parsing
    return form;
}

void Request::setMethod(const RequestMethod &method) {
    this->method = method;
}

void Request::setPath(const std::string &path) {
    this->path = path;
}

string *Request::getUriPattern() const {
    return uriPattern;
}

void Request::setUriPattern(string *uriPattern) {
    Request::uriPattern = uriPattern;
}

RequestMethod Request::getRequestMethodFromString(const std::string &val) {
    if ("GET" == val) return RequestMethod::GET;
    if ("POST" == val) return RequestMethod::POST;
    if ("PUT" == val) return RequestMethod::PUT;
    if ("DELETE" == val) return RequestMethod::DELETE;
    if ("HEAD" == val) return RequestMethod::HEAD;

    throw HttpServerException("Unexpected request method!");
}

void Request::parseHttpStatusLine(Request &request, std::istringstream &f) {
    std::string statusLine;
    std::getline(f, statusLine);

    std::string s;
    std::istringstream issStatus(statusLine);

    getline(issStatus, s, ' ');
    request.setMethod(getRequestMethodFromString(s));

    getline(issStatus, s, ' ');
    request.setPath(s);
}

void Request::parseHeaderLine(Request &request, const std::string &headerLine) {
    unsigned long delimiterPos = headerLine.find(':');
    const std::string &name = headerLine.substr(0, delimiterPos);
    std::string values = headerLine.substr(delimiterPos + 1);
    if (" " == values.substr(0, 1))
        values = values.substr(1);

    std::istringstream issHeaderVals(values);
    std::string valLine;
    while (getline(issHeaderVals, valLine, ','))
        request.Header().Add(name, valLine);
}

void Request::parseHttpHeadersLines(Request &request, std::istringstream &f) {
    std::string headerLine;
    while (getline(f, headerLine)) {
        headerLine = headerLine.substr(0, headerLine.length() - 1);
        if (headerLine.empty()) // headers finished, start body
            return;
        parseHeaderLine(request, headerLine);
    }
}

Request net::http::parseRequest(const std::string &raw) {
    Request request;
    std::istringstream f(raw);
    Request::parseHttpStatusLine(request, f);
    Request::parseHttpHeadersLines(request, f);
    return request;
}
