//
// Created by bradl on 2022-10-29.
//

#ifndef A3_SERVERSOCKET_HPP
#define A3_SERVERSOCKET_HPP

#include "ServerSocket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <cstdio>


class ServerSocket {


public:
    ServerSocket()=default;
    ServerSocket(int port);
    Socket* accept();


private:
    int port;
};


#endif //A3_SERVERSOCKET_HPP
