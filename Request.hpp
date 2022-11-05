#pragma once

#include <iostream>
#include <sstream>
// #include <unordered_map>
#include <string>
#include <map>
#include <iterator>

using namespace std;

class Request
{

public:
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

    string getReqMethod()
    {
        return reqType;
    }

    string getUserAgent()
    {
        return reqUserAgent;
    }

    istringstream *getInputStream()
    {
        return inputStream;
    }

    string getFormData(string key)
    {
        // string found = FormDataMap.find(key);
        return FormDataMap.at(key);
    }

    string getImageByteCode()
    {
        return imageByteCode;
    }

private:
    istringstream *inputStream;
    string reqType;
    string reqUserAgent;
    multimap<string, string> FormDataMap;
    string imageByteCode;
};