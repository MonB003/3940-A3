// #include "Socket.hpp"
// #include "ServerSocket.hpp"
#include "Thread.hpp"
#include "ServerThread.hpp"
#include "ServerSocket.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include <stddef.h>
#include <sys/socket.h>
#include <sys/dir.h>
#include <resolv.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
// #include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <cstring>

// g++ main.cpp ServerThread.cpp Request.cpp ServerSocket.cpp Response.cpp Socket.cpp UploadServlet.cpp -o main

using namespace std;

/**
    main function.
*/
int main()
{

    struct sockaddr_in server;
    int msgsock;
    char buf[1024];
    // struct hostent *host;
    char *host = "127.0.0.1"; // local host address
    int rval;
    // char* html = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 600\n\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title> File Upload Form</title>\r\n</head>\r\n<body>\r\n<h1>Upload file</h1>\r\n<form id =\"form\" method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n<input type=\"file\" name=\"fileName\"><br/><br/>\r\nCaption: <input type =\"text\" name=\"caption\"><br/><br/>\r\n <br/>\nDate : <input type=\"date\" name=\"date\"><br/><br/>\r\n <br/>\n <input id='formBtn' type=\"submit\" name=\"submit\" value=\"Submit\">\r\n </form>\r\n</body>\r\n</html>\r\n";

    ServerSocket *socket = new ServerSocket(8880); // socket creation.

    while (socket != NULL)
    {
        cout << "NOT NULL" << endl;

        Socket *currentSocket = socket->Accept();
        cout << "here in mnain" << endl;
        ServerThread *serverThread = new ServerThread(currentSocket);
        serverThread->run();
        Request *request = serverThread->getRequest(); 
        Response *response = serverThread->getResponse();
        cout << "req method: " << request->getReqMethod() << endl;
        string responseStr = response->sendBack("");
        char *resPtr = const_cast<char *>(responseStr.c_str());
        currentSocket->sendResponse(resPtr); // serve the html.
        close(currentSocket->getSocket());
    }
    close(socket->getPort());

    cout << "here" << endl;
    return 0;
}
