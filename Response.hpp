#pragma once

#include <sstream>
#include "Socket.hpp"
#include <iostream>
using namespace std;

class Response{

public:
    static string HTTP_VERSION;

    Response(){
        
    };

    void send(string page);

    void createHeader();
    // byte[] createByteArray();

private:
    // PrintWriter printWriter;
    string characterEncoding;
    string contentType;
    // ByteArrayOutputStream out;
    // ByteArrayOutputStream outStream = new ByteArrayOutputStream();
    // DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("yyyy,MM,dd HH:mm:ss");
   // Socket socket;

};

string Response::HTTP_VERSION = "HTTP/1.1 OK";