#ifndef THREAD_HPP_INCLUDED
#define THREAD_HPP_INCLUDED

#include<thread>
#include <iostream>


using namespace std;

class Thread{

private:

    Thread* msgsocket;
	void *state;

public:
    Thread(Thread* msgsock){
        this->msgsocket = msgsock;
        this->state = malloc(sizeof(pthread_t));
};
    ~Thread(){};
    static void* run(void* socketNumber){
    std::cout << "hello" << std::endl;
    return(void*) 1;
}
;
     void start(){
     pthread_t threadID; // creates the new thread;

        // runs on creation.
    pthread_create(&threadID,NULL,run,(void*)this);
};
};

#endif // THREAD_HPP_INCLUDED
