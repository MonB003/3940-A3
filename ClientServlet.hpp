#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED

#include <iostream>
#include <sstream>
#include <dirent.h>
#include <exception>
#include <string>
#include <fstream>
#include "base64.hpp"


using namespace std;

class ClientServlet {


public:
    ClientServlet();
    void getUserInput();
    void POSTRequest();
    string encodeImage(string);
    // static char* ReadAllBytes(const char* filename);

    string getImagePath() {
        return imagePath;
    }

    string getMultiKeyword() {
        return MultiKeyword;
    }

    string getMultiCaption() {
        return MultiCaption;
    }

    string getMultiDate() {
        return MultiDate;
    }

    void setImagePath(string imagePath) {
        this->imagePath = imagePath;
    }

    void setMultiKeyword(string MultiKeyword) {
        this->MultiKeyword = MultiKeyword;
    }

    void setMultiCaption(string MultiCaption) {
        this->MultiCaption = MultiCaption;
    }

    void setMultiDate(string getMultiDate) {
        this->MultiDate = MultiDate;
    }

private:
    string imagePath;
    string MultiKeyword;
    string MultiCaption;
    string MultiDate;
    unsigned char* imagebase64;
    int portNumber = 8889;
};


#endif // CLIENT_HPP_INCLUDED