#include "Thread.hpp"
#include <iostream>

using namespace std;

class ServerThread: public Thread {


public:

    ServerThread(int msgSock): Thread(this){
        cout<< "creating server thread" <<endl;
    this->msgsocket = msgSock;
    
};
    void run(){

    cout << "here in run method" << endl;
};
    ~ServerThread();
private:
     int msgsocket;
};