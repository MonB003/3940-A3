#pragma once

#include <sstream>
#include "Socket.hpp"
#include <iostream>
#include <ctime>

#define HTTP_VERSION "HTTP/1.1 OK"

using namespace std;

class Response {

public:
    Response(ostringstream *outStream) {
        this->outStream = outStream;
    };

    Response(Socket socket, ostringstream *outStream){
        this->outStream = outStream;
        this->socket = socket;
    }


    void send(string page){
            ostream out = socket.getOutputStream();
            string htmlPage = page;
            string CRLF = "\r\n"; // need this line
            string response = "HTTP/1.1 200 OK";
            response.append(CRLF);
            response.append("Content-Length: ");
            stringstream pageLenStream;
            pageLenStream << htmlPage.length();
            string pageLength = pageLenStream.str();
            response.append(pageLength);
            response.append(CRLF);
            response.append(CRLF);
            response.append(htmlPage);
            response.append(CRLF);
            response.append(CRLF);

            out << response; // renders the page.
    };

    void createHeader() {
        time_t ttime = time(0);
        char* dt = ctime(&ttime);
        string headerString = "GET / HTTP/1.1 OK\r\nDate: ";
        headerString.append(dt);
        headerString.append("\r\nContent-Type: ");
        headerString.append(contentType);
        headerString.append("\r\n");
        headerString.append("Character-Encoding:");
        headerString.append(characterEncoding);
        headerString.append("\r\n");
        *outStream << headerString;
    }

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