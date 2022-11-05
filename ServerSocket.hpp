#pragma once

#include "Socket.hpp"

class ServerSocket{

private:
    int sock;

public:
	int getPort(){return this->sock;};
    ServerSocket(int port);
    Socket* Accept();
    ~ServerSocket();
};