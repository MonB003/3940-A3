#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ostream>

using namespace std;

class Socket
{
public:
	Socket() = default;
	Socket(int sock);
	char* getRequest();
	void sendResponse(char* res);
	ostream getOutputStream();
	~Socket();
private:
	int sock;
};

