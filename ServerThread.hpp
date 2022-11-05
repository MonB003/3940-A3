#include "Thread.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include "Servlet.hpp"
#include "UploadServlet.hpp"

//constexpr string url ="localhost:8888";

using namespace std;

// Router
class ServerThread : public Thread
{

public:
     ServerThread(int msgSock);

    int renderHTML();

    void parseRequest();

    void run();

    void runMethod(string &method,  Response *res,  Request *req, Servlet &up);

    ~ServerThread() = default;

private:
    int msgsocket; // socket reference.
};