// #include "Socket.hpp"
// #include "ServerSocket.hpp"
#include "Thread.hpp"
#include "ServerThread.hpp"
#include "../Socket/ServerSocket.hpp"

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



    // socket creation
    // int listening = socket(AF_INET,SOCK_STREAM,0);
    // if(listening == -1){
    //     std::cerr<<"Cant create a scocket";
    //     return -1;
    // }else {
    //     cout << "Socket Created..."<<endl;
    // }


    // server.sin_family = AF_INET;
    // server.sin_addr.s_addr = INADDR_ANY;
    // server.sin_port = htons(8888);
   // server.sin_port = htons(54000); // can try this too if theres errors, refers to endianess
    //inet_pton(AF_INET,"0.0.0.0", &server.sin_addr);

    // int bound = bind(listening, (struct sockaddr*)&server, sizeof(server)) ;
    // cout << "bound: " << bound <<endl;

    // if(bound == - 1){
    //     perror("Cannot Bind");
    //     return -2;
    // }

    // listen(listening, 5);

    ServerSocket *socket = new ServerSocket(8888);

    while(socket != null){
        Socket *currentSocket = socket->Accept();
    }

    // while(1){
    //     cout <<"entering thread" <<endl;

    //     msgsock = accept(listening, (struct sockaddr*) 0, (socklen_t*) 0 );

    //     if(msgsock == -1){
    //         perror("accept");
    //     }



    //     connect(msgsock, (struct sockaddr*)&server, sizeof(server));



    //    // new thread
    //     cout <<"creating thread" <<endl;

    //     ServerThread* serverThread = new ServerThread(msgsock);
    //     serverThread -> run();
    // }

    close(msgsock);


cout<<"here"<<endl;
    return 0;
}




