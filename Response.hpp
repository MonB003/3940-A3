#pragma once

#include <sstream>
#include "Socket.hpp"
#include <iostream>
#include <ostream>

#include <ctime>
#include <fstream>

#define HTTP_VERSION "HTTP/1.1 OK"

using namespace std;

class Response {

public:
    Response(ostringstream *outStream);

    Response(Socket socket, ostringstream *outStream);

    void send(string page);

    void createHeader();

    ostream* getOutputStream() {
        return oStream;
    }

    char* createByteArray();
    
    ostringstream* getByteArray();

    ostream* getWriter() {
        return oStream;
    }

    void setCharacterEncoding(string string) {
        this->characterEncoding = string;
    }

    void setContentType(string string) {
        this->contentType = string;
    }


private:
    string characterEncoding;
    string contentType;
    ostringstream* outStream;
    ostream* oStream;
    Socket socket;

};