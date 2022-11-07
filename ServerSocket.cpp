

#include "ServerSocket.hpp"

ServerSocket::ServerSocket(int port)
{

    sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    int bound = bind(sock, (struct sockaddr *)&server, sizeof(server));
   // cout << "bound: " << bound << endl;
    listen(sock, 5);

    cout <<"Attempting a connection"<<endl;

};

Socket *ServerSocket::Accept()
{
      cout <<"Attempting an accept of the socket"<<endl;

  sockaddr_in localAddr, remoteAddr;
	int addrLen = sizeof (remoteAddr);
	int cSock = accept(sock, (struct sockaddr*) 0, (socklen_t*) 0 );
  cout << "Sock int: " << cSock <<endl;
	Socket *cs = new Socket(cSock);
	return cs;
}