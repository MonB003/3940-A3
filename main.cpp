#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "ServerSocket.hpp"
#include "Socket.hpp"
#include <exception>

using namespace std;

int main() {

    ServerSocket *serverSocket =  new ServerSocket(8999);



    if(serverSocket != NULL){
        Socket *connection = serverSocket->Accept();
        char* req = connection -> getRequest(); // request
        char* res = new char(50); // response
        connection -> sendResponse(res); 
    }


    
    return 0;
}
