#include "Client.hpp"


Client::Client(){};

void Client::getUserInput() {
    cout << "Please enter the file path for the image:" << endl;
    cin >> imagePath;
    cout << "Image Path: " << imagePath << endl;

    cout << "Please enter a Keyword for the image:" << endl;
    cin >> MultiKeyword;
    cout << "Keyword: " << MultiKeyword << endl;

    cout << "Please enter a Caption for the image:" << endl;
    cin >> MultiCaption;
    cout << "Caption: " << MultiCaption << endl;
}
