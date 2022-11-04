#include "Thread.hpp"
#include <sys/socket.h>
#include <iostream>

using namespace std;

// Router
class ServerThread : public Thread
{

public:
    ServerThread(int msgSock) : Thread(this)
    {
        cout << "creating server thread" << endl;
        this->msgsocket = msgSock;
    };

    // get ---- request class
    void get(){};

    // post ---- request class
    void post()
    {
        char arr[1024] = "HTTP/1.1 200 OK\r\n\r\n<html>\n\r<body>\n\r\rhello\n\r</body>\n</html>";
        int send_res = send(msgsocket, arr, sizeof(arr), 0);
        if (send_res == -1)
        {
            perror("send");
        }
        else
        {
            cout << "send success\n";
        }
    }

    void renderHTML()
    {

//<!DOCTYPE html>\r\n<html>\r\n< head >\r\n< title > File Upload Form</ title>\r\n< / head >\r\n< body >\r\n
// \r\n</body>\r\n</html>\r\n
        string html = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 600\n\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title> File Upload Form</title>\r\n</head>\r\n<body>\r\n<h1>Upload file</h1>\r\n<form id =\"form\" method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n<input type=\"file\" name=\"fileName\"/><br/><br/>\r\nCaption: <input type =\"text\" name=\"caption\"<br/><br/>\r\n <br/>\nDate : <input type=\"date\" name=\"date\"<br/><br/>\r\n <br/>\n <input id='formBtn' type=\"submit\" name=\"submit\" value=\"Submit\"/>\r\n </form>\r\n</body>\r\n</html>\r\n";

        char arr[200] = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 16\n\n<h1>testing</h1>";
        int send_res = send(msgsocket, html.c_str(), html.length(), 0); // 
        // do a response...
    }

    // display html
    void run()
    {

        cout << "here in run method" << endl;
        renderHTML();
    };
    ~ServerThread();

private:
    int msgsocket;
};