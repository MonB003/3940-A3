#pragma once

#include <sstream>
// #include "Socket.hpp"
#include <iostream>
#include <ostream>
#include <sys/socket.h>


#include <ctime>
#include <fstream>

#define HTTP_VERSION "HTTP/1.1 OK"

using namespace std;

class Response {

private:
    string characterEncoding;
    string contentType;
    ostringstream* outStream;
    ostream* oStream;
    //Socket socket;
    int socket;

public:
    Response(ostringstream *outStream);

    Response(int socket, ostringstream *outStream);

    void sendBack(string page);

    void createHeader();

    ostream* getOutputStream() {
        return oStream;
    }

    unsigned char* createByteArray();
    
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




};