#ifndef THREAD_HPP_INCLUDED
#define THREAD_HPP_INCLUDED

#include<thread>
#include <iostream>


using namespace std;

class Thread{

private:

    Thread* msgsocket;

public:
    Thread(Thread* &msgsock);
    ~Thread();
    static void* run(void* socketNumber);
     void start();
};

#endif // THREAD_HPP_INCLUDED
