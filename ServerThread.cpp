#include "ServerThread.hpp"

ServerThread::ServerThread(int msgSock) : Thread(this)
{
    this->msgsocket = msgSock;
}

int ServerThread::renderHTML()
{
    string html = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 600\n\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title> File Upload Form</title>\r\n</head>\r\n<body>\r\n<h1>Upload file</h1>\r\n<form id =\"form\" method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n<input type=\"file\" name=\"fileName\"/><br/><br/>\r\nCaption: <input type =\"text\" name=\"caption\"<br/><br/>\r\n <br/>\nDate : <input type=\"date\" name=\"date\"<br/><br/>\r\n <br/>\n <input id='formBtn' type=\"submit\" name=\"submit\" value=\"Submit\"/>\r\n </form>\r\n</body>\r\n</html>\r\n";

    char arr[200] = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 16\n\n<h1>testing</h1>";

    int send_res = send(msgsocket, html.c_str(), html.length(), 0); //
    // do a response...
    return send_res;
}

void ServerThread::runMethod(string &method, Response *res, Request *req, Servlet &up)
{
    if (method == "GET") {
        cout << "-------------------------------2. METHOD: " << method << endl;
        int responseInt = up.get(*res, *req);


        // if (responseInt != -1) {

        // }

        // char buffer[1024 * 1024];
        // int receiveInt = recv(up.getSocket(), &buffer, 1024 * 1024, 0);
        cout <<"Response int: "<<responseInt << endl;

        
    } else {
        cout <<"-------------------------------3. METHOD: " << method<<endl;
        up.get(*res, *req);
        up.post(*res, *req);
    }

    cout << "in method call" << endl;
}

void ServerThread::run()
{
    char buffer[1024 * 1024];

    // writes to the socket 
    recv(msgsocket, &buffer, 1024 * 1024, 0);

    // istringstream requestInfo = buffer.c_str();
    istringstream requestInfo(buffer);
    istringstream *reqPtr = &requestInfo;

    // Servlet *up = nullptr;

    UploadServlet *up = new UploadServlet{msgsocket};

    ostringstream *outputWriter = new ostringstream();
    Response *response = new Response(msgsocket, outputWriter);
    Request *request = new Request(reqPtr);
    string requestMethod = request->getReqMethod();
    cout << "METHOD: [" << requestMethod << "]" << endl;


    string locationOfRequest = request -> getUserAgent();

    // if (locationOfRequest == "browser")
    // {
    //     up = (UploadServlet) new UploadServlet();
    // }
    // else if (locationOfRequest == "cli")
    // {
    //     // up = new ClientServlet();
    // }
    runMethod(requestMethod, response, request, *up);

    // send(msgsocket,get_http, strlen(get_http.c_str()),0 );

    cout << "here in run method" << endl;
}
