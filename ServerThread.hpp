#include "Thread.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include "Servlet.hpp"
#include "UploadServlet.hpp"
#include "Socket.hpp"

//constexpr string url ="localhost:8888";

using namespace std;

// Router
class ServerThread : public Thread
{

public:
    ServerThread(Socket* msgSock);
    int renderHTML();

    void parseRequest();

    string run();
    void getDataFromSocket(Socket* messageSocket);
    void runMethod(string &method,  Response *res,  Request *req, Servlet &up);

    ~ServerThread() = default;
    Request* getRequestObject(){
        return this->request;
    }

    Response* getResponse() {
        return this->response;
    }
private:
    Socket* msgsocket; // socket reference.
    Request *request;
    Response *response;

};