#include "Thread.hpp"
#include <sys/socket.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string readFile(string filename){
    // Open declared File - <fstream> header for file Reading and Writing
    std::fstream f{filename};
    filename = filename + "<h1>HTML Forms</h1>\n";

    // Can manually open as well
    //    f.open("data.txt");

    // String for output
    std::string input;
    string output;
    string intermediate;
    output.append("HTTP/1.1 200 OK\n");
    output.append("Content-Type:text/html\n");
    output.append("Content-Length: ");

    if (f.is_open()){

        // Keep getting next Line
        while(std::getline(f,input)){
            intermediate.append(input);
            intermediate.append("\n");
        }
        f.close();
    }

    output.append(to_string(intermediate.length()));
    output.append("\n\n");
    output.append(intermediate);

    return filename;
}
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
// "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 14\n\n<h1>Hell<h1>\n"
        string html = readFile("HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 100\n\n<h2>Hell<h2>");
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