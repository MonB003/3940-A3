#include "Socket.hpp"
#include "ServerSocket.hpp"
#include "Thread.hpp"
#include "ServerThread.hpp"

#include <stddef.h>
#include <sys/socket.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <string>


using namespace std;

/**
    main function.
*/
main() {

    struct sockaddr_in server;
    int msgsock;
    char buf[1024];
    struct hostent *hp;
    char *host = "127.0.0.1"; // local host address
    int rval;
    pthread_t thread_id;

    // socket creation
    int listening = socket(AF_INET,SOCK_STREAM,0);
    if(listening == -1){
        std::cerr<<"Cant create a scocket";
        return -1;
    }else {
        cout << "Socket Created..."<<endl;
    }


    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
   // server.sin_port = htons(54000); // can try this too if theres errors, refers to endianess
    //inet_pton(AF_INET,"0.0.0.0", &server.sin_addr);

    int bound = bind(listening, (struct sockaddr*)&server, sizeof(server)) ;
    cout << "bound: " << bound <<endl;

    if(bound){
        perror("Cannot Bind");
        return -2;
    }

    listen(listening, 5);

    while(1){
        cout <<"entering thread" <<endl;

        msgsock = accept(listening, (struct sockaddr*) 0, (socklen_t*)0);

        cout<< "message socket: " << msgsock << endl;
        if(msgsock == -1){
            perror("accept");
        }

        

       // new thread
        cout <<"creating thread" <<endl;
        ServerThread* serverThread = new ServerThread(msgsock);
        serverThread -> run();



      
    }


  //  if(connect(listening, (struct sockaddr*)&server, sizeof(server))<0 ){
   //     perror("connection issue");
   // }



 // ServerSocket *ss = new ServerSocket(8888);
	//if (ss != NULL) {
		//Socket *cs = ss->Accept();
	//	char *req = cs->getRequest();
	//	char *res = new char(50);
	//	cs->sendResponse(res);
//	}
    close(listening);
    return 0;
}




