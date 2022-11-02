#pragma once

#include "Thread.hpp"
#include "Socket.hpp"

class Router : public Thread {
    private:
        Socket socket;

    public:
        Router(Socket socket) : socket(socket) {};
        void run() override;
}