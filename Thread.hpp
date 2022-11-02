#pragma once

#include "ServerSocket.hpp"

class Thread {
public:
	Thread(Thread *childThread);
	~Thread();
	virtual void run() {}
	void start();
private:
	void *state;
	Thread *childThread;
};
