//
// Created by bradl on 2022-10-30.
//

#ifndef A3_SOCKET_HPP
#define A3_SOCKET_HPP


class Socket {

private:
    int socket;
public:
    Socket(int socket);
    char* getRequest();
    void sendResponse(char* c);
    ~Socket();

};


#endif //A3_SOCKET_HPP
