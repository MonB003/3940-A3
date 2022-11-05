#pragma once
#include "Socket.hpp"
class ServerSocket
{
public:
	ServerSocket(int port);
	Socket* Accept();
	~ServerSocket();
private:
	int sock;
};

