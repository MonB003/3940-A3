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


using namespace std;

/**
    main function.
*/
int main() {

    struct sockaddr_in server;
    int msgsock;
    char buf[1024];
    //struct hostent *host;
    char *host = "127.0.0.1"; // local host address
    int rval;

    ServerSocket *socket = new ServerSocket(8897); // socket creation.





    while(socket != NULL){
          cout<<"NOT NULL"<<endl;
          
        Socket *currentSocket = socket -> Accept(); 
        cout << "here in mnain" <<endl;
        ServerThread* serverThread = new ServerThread(currentSocket);
        serverThread -> run();
        // Request* request   = serverThread -> getRequest(); /// serVerthread return req
        // Response* response = serverThread -> getResponse();
        // string responseStr = response-> sendBack("");
        // char* resPtr       = const_cast<char *>(responseStr.c_str());
        // currentSocket -> sendResponse(resPtr);
        
       close(currentSocket->getSocket());
    }
    close(socket->getPort());


cout<<"here"<<endl;
    return 0;
}




