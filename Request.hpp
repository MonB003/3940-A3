#pragma once

#include <iostream>
using namespace std;

class Request{


public:
    Request() = default;

    void parsePayload();

    void setReqType(string reqType) {
        this.reqType = reqType;
    }

    string getReqMethod() {
        return reqType;
    }

    string getUserAgent() {
        return reqUserAgent;
    }

    void setUserAgent(string userAgent) {
        this.reqUserAgent = userAgent;
    }

private:
    string reqType;
    string reqUserAgent;

};