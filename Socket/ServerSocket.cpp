

#include "ServerSocket.hpp"

ServerSocket::ServerSocket(int port) : port(port)
{

    int listening = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    int bound = bind(listening, (struct sockaddr *)&server, sizeof(server));
    cout << "bound: " << bound << endl;
    listen(listening, 5);
};

Socket *ServerSocket::Accept()
{
    sockaddr_in localAddr, remoteAddr;
	int addrLen = sizeof (remoteAddr);
	int cSock = accept(sock, (struct sockaddr *)&remoteAddr, &addrLen);
	Socket *cs = new Socket(cSock);
	return cs;
}