#include <string>
#include <sys/socket.h>
#include "Response.hpp"
#include "Request.hpp"
#include <iostream>
#include <dirent.h>
#include <resolv.h>

#include <time.h>
#include <vector>
#include <algorithm>
#include "Servlet.hpp"


#include <sys/dir.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
using namespace std;

class UploadServlet : public Servlet {

private:
    int socket;
public:
    UploadServlet(int socket);
    UploadServlet() = default;
    //UploadServlet(const UploadServlet &up) = default;

    int getSocket() override;
    
    void post(Response &response, Request &request) override;
    
    string get(Response &response, Request &request) override;
    string getListing(); 

};