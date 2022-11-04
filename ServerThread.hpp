#include "Thread.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <sys/socket.h>
#include <iostream>
#include <sstream>


//constexpr string url ="localhost:8888";

using namespace std;

// Router
class ServerThread : public Thread
{

public:
    //Response res;
    //Request req;
    ServerThread(int msgSock) : Thread(this)
    {
        cout << "creating server thread" << endl;
        this->msgsocket = msgSock;
    };

    // get ---- request class
    void get(){
        cout <<"get request called"<< endl;
    };

    // post ---- request class
    void post()
    {
        

    //     char arr[1024] = "HTTP/1.1 200 OK\r\n\r\n<html>\n\r<body>\n\r\rhello\n\r</body>\n</html>";
    //    int send_res = send(msgsocket, arr, sizeof(arr), 0);

    //   //  int send_res = writev(msgsocket, arr,sizeof(arr));
        
    //     if (send_res == -1)
    //     {
    //         perror("send");
    //     }
    //     else
    //     {
    //         cout << "send success\n";
    //     }
    }

    int renderHTML()
    {

        string html = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 600\n\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title> File Upload Form</title>\r\n</head>\r\n<body>\r\n<h1>Upload file</h1>\r\n<form id =\"form\" method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n<input type=\"file\" name=\"fileName\"/><br/><br/>\r\nCaption: <input type =\"text\" name=\"caption\"<br/><br/>\r\n <br/>\nDate : <input type=\"date\" name=\"date\"<br/><br/>\r\n <br/>\n <input id='formBtn' type=\"submit\" name=\"submit\" value=\"Submit\"/>\r\n </form>\r\n</body>\r\n</html>\r\n";

        char arr[200] = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 16\n\n<h1>testing</h1>";


       int send_res = send(msgsocket, html.c_str(), html.length(), 0); // 
        // do a response...
        return send_res;
    }

    // display html

    void parseRequest(){};

    void run()
    {

       // string get_http = "GET / HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

       // res = new Response(msgsocket); // socket stream in

        char buffer[1024*1024];

        recv(msgsocket, &buffer, 1024*1024,0);

        // istringstream requestInfo = buffer.c_str();
        istringstream requestInfo(buffer);
        istringstream *reqPtr = &requestInfo;
        cout << buffer <<endl;
        Request *req = new Request(reqPtr);

       

        //send(msgsocket,get_http, strlen(get_http.c_str()),0 );

        cout << "here in run method" << endl;
        // we should distinguish between get and post here.....
        int res = renderHTML();
        cout << res <<endl;








    };
    ~ServerThread();

private:
    int msgsocket; // socket reference.
};