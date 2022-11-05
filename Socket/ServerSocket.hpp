#pragma once

#include "Socket.hpp"

class ServerSocket{

private:
    int port;

public:

    ServerSocket(int port);
    Socket* Accept();
    ~ServerSocket();
};