#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ostream>
#include <iostream>


using namespace std;

class Socket
{
public:
	Socket() = default;
	Socket(int sock);
	string getRequest();
	void sendResponse(char* res);
	ostream getOutputStream();
	~Socket();
	int getSocket(){
		return this->sock;
	}
private:
	int sock;
};

