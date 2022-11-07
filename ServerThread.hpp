#include "Thread.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include "Servlet.hpp"
#include "UploadServlet.hpp"
#include "Socket.hpp"
#include <fstream>

//constexpr string url ="localhost:8888";

using namespace std;

// Router
class ServerThread : public Thread
{

public:
     //ServerThread(int msgSock);
     ServerThread(Socket* msgSock);
    int renderHTML();

    void parseRequest();
    string readSocket();
    string run();

    void runMethod(string &method,  Response *res,  Request *req, Servlet &up);

    ~ServerThread() = default;
    Request* getRequest(){
        return this->request;
    }

    Response* getResponse() {
        return this->response;
    }



    void writeFile(string content);
    // void writeFile(string content) {
    //     cout << "WRITE FILE" << endl;
    //     // FILE *filePointer = nullptr;
    //     // char *test = "test.txt";

    //     // char buffer[1];

    //     // filePointer = fopen(test, "w");

    //     cout << "OPEN FILE" << endl;


       

    //     // int num;
    //     // while (1) {
    //     //      cout << "IN LOOP" << endl;
    //     //     num = recv(msgsocket->getSocket(), buffer, 1, 0);

    //     //     cout << "RECEIVE" << endl;
    //     //     if (num <= 0) {
    //     //          cout << "NUM IS 0" << endl;
    //     //         break;
    //     //     }
    //     //      cout << "AFTER IF" << endl;
    //     //     fprintf(filePointer, "%s", content);

    //     //     cout << "AFTER WRITE" << endl;

    //     //     bzero(buffer, content.length());
    //     // }


    //     ofstream myfile;
    //     myfile.open("test.txt");
        

    //     while (true) {
    //         int find1 = content.find("name=\"fileName\";");
    //         string substr1 = content.substr(find1, content.length());
    //         int find2 = substr1.find("\r\n");
    //         string substr2 = substr1.substr(find2, content.length());

    //         cout << "-------------------FOUND FILENAME" << endl;
    //         cout << substr1 << endl;
    //         cout << substr2 << endl;

    //         myfile << substr2 << "\n";

    //         // if (content.find("name=\"filename\"") != std::string::npos) {
    //         //     cout << "-------------------FOUND FILENAME" << endl;
    //         //     cout << content << endl;
    //         //     if (content.find("\r\n") != std::string::npos) {
                    
    //         //     }
    //         // }
    //     }
    //     myfile.close();

    // }


private:
    Socket* msgsocket; // socket reference.
    Request *request;
    Response *response;

};