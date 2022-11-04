#pragma once
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

