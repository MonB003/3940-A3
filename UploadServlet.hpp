#include <string>
#include <sys/socket.h>
#include "Response.hpp"
#include "Request.hpp"
#include <iostream>
#include <dirent.h>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

class UploadServlet{

private:


public:

    void post(Response response, Request request){
        // TODO 
        ostringstream oss;
        istringstream in = req.getInputStream();
        unsigned char* content;
        while (in >> content)
        {
            oss << content;
        }
        time_t timer;
        struct tm y2k = {0};
        y2k.tm_hour = 0;
        y2k.tm_min = 0;
        y2k.tm_sec = 0;
        y2k.tm_year = 100;
        y2k.tm_mon = 0;
        y2k.tm_mday = 1;
        long seconds;

        time(&timer);
        seconds = difftime(timer, mktime(&y2k));

        
        string filename = "./images/";
        filename.append(seconds);
        filename.append(".png");
        //may need to set write mode to base64 if we end up doing that again, not totally sure how
        ofstream fileOut(filename);
        string byteStr = oss.str();
        fileOut << byteStr;
        fileOut.close();

        DIR *directory;
        struct dirent *currFile;
        directory = opendir("./images");  // Gets all files in the images folder
        vector<string> fileNames;
        if (directory) {
            while ((currFile = readdir(directory)) != nullptr) {
                fileNames.push_back(currFile->d_name);
            }
        }
        sort(fileNames.begin(), fileNames.end());
        int i = 1;
        for(string str : fileNames){
            cout << "Image " << i << ": " << str << endl;
            i++;
        }
        closedir(directory);
    }

    void get(Response response, Request Request){
        string html = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 600\n\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title> File Upload Form</title>\r\n</head>\r\n<body>\r\n<h1>Upload file</h1>\r\n<form id =\"form\" method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n<input type=\"file\" name=\"fileName\"/><br/><br/>\r\nCaption: <input type =\"text\" name=\"caption\"<br/><br/>\r\n <br/>\nDate : <input type=\"date\" name=\"date\"<br/><br/>\r\n <br/>\n <input id='formBtn' type=\"submit\" name=\"submit\" value=\"Submit\"/>\r\n </form>\r\n</body>\r\n</html>\r\n";
        int send_res = send(msgsocket, html.c_str(), html.length(), 0); 
    }


    string getListing() {
        string dirList =  "<ul>";
        DIR *directory;
        struct dirent *currFile;
        directory = opendir("./images");  // Gets all files in the images folder
        if (directory) {
            while ((currFile = readdir(directory)) != nullptr) {
                cout << currFile->d_name << endl;
                dirList.append("<li>");
                dirList.append(currFile->d_name);
                dirList.append("</li>");  
            }
        }
        closedir(directory);
    
        dirList.append("</ul>");
         
        return dirList;
    } 

};