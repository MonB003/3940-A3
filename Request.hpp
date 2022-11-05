#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
// #include "Servlet.hpp"

using namespace std;

class Request
{
private:
    istringstream *inputStream;
    string reqUserAgent;
    map<string, string> FormDataMap;
    string imageByteCode;
public:

    string reqType;

    Request();

    Request(istringstream *inStream);

    void parsePayload(istringstream *inStream);

    void setReqType(string reqType)
    {
        this->reqType = reqType;
    }

    void setUserAgent(string userAgent)
    {
        reqUserAgent = userAgent;
    }

    string getReqMethod();

    string getUserAgent()
    {
        return reqUserAgent;
    }

    istringstream *getInputStream()
    {
        return inputStream;
    }

    pair<string, string> getFormData(string key)
    {
        // string found = FormDataMap.at(key);
        return *FormDataMap.find(key);
    }

    string getImageByteCode()
    {
        return imageByteCode;
    }

    void loopLine(string line, map<string, string> FormDataMap);


};