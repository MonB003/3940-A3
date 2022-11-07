#include "ServerThread.hpp"

ServerThread::ServerThread(Socket *msgSock) : Thread(this)
{
    this->msgsocket = msgSock;
}

int ServerThread::renderHTML()
{
    string html = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 600\n\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title> File Upload Form</title>\r\n</head>\r\n<body>\r\n<h1>Upload file</h1>\r\n<form id =\"form\" method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n<input type=\"file\" name=\"fileName\"/><br/><br/>\r\nCaption: <input type =\"text\" name=\"caption\"<br/><br/>\r\n <br/>\nDate : <input type=\"date\" name=\"date\"<br/><br/>\r\n <br/>\n <input id='formBtn' type=\"submit\" name=\"submit\" value=\"Submit\"/>\r\n </form>\r\n</body>\r\n</html>\r\n";

    char arr[200] = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 16\n\n<h1>testing</h1>";

    int send_res = send(msgsocket->getSocket(), html.c_str(), html.length(), 0); //
    // do a response...
    return send_res;
}

string ServerThread::readSocket()
{
    char character[1];
    string fileData;
    int r;

    cout << "START OF READSOCKET LOOP" << endl;

    while (r = recv(msgsocket->getSocket(), &character, 1, 0) == 1)
    {
        cout << *character << endl;
        fileData += *character;
        // cout << "R VAL: " << r << endl;
    }

    //     char* requestPtr = (char*)malloc(fileData.length() + 1);
    //     char arr[fileData.length()];
    //     strcpy(arr, fileData.c_str());

    //   //  cout << "FILE DATA LOOP" << endl;
    //     for(int i = 0; i < fileData.length(); i++){
    //         requestPtr[i] = arr[i];
    //   //      cout << "file character: " << requestPtr[i] <<endl;;

    //     }

    // requestPtr[fileData.length()] = '\0';
    // cout<<"---------------------------------------"<<endl;
    // cout << requestPtr << endl;

    cout << "END OF READSOCKET LOOP" << endl;

    return fileData;
}

void ServerThread::runMethod(string &method, Response *res, Request *req, Servlet &up)
{
    if (method == "GET")
    {
        cout << "-------------------------------2. METHOD: " << method << endl;
        int responseInt = up.get(*res, *req);

        cout << "Response int: " << responseInt << endl;
    }
    else
    {
        cout << "-------------------------------3. METHOD: " << method << endl;
        up.get(*res, *req);
        up.post(*res, *req);
    }

    cout << "in method call" << endl;
}

string ServerThread::run()
{
    int bufferSize = 1;
    
   // char buf1[1024*1024];

    char buf[bufferSize];

    char allDataBuffer[1024*1024];

    int i = 0;
    int rval;
    string patternGet = "GET";
    string patternPost = "POST";
    string patternBoundary = "WebKitFormBoundary"; // "boundary=----";
    string pattern = "\r\n\r\n";

    char buf2[526336];
    bool checkBoundary = false;
    int j = 0;

    bool isGet = false;
    bool isPost = false;

    bool startByteCode = false;
    bool endByteCode = false;
    string boundaryCheckString = "";
    int bufferIndex = 0;
    //string data ="";

    bool reading = true;
    while ( rval = read(msgsocket->getSocket(), buf, bufferSize) > 0)
    {
        //rval = read(msgsocket->getSocket(), buf, bufferSize);

        allDataBuffer[bufferIndex] = *buf;      
        string data{allDataBuffer};
        bufferIndex++;

        // each line of the request.
        if(*buf == '\n'){

            cout << "LINE: " << data << endl;
        }


        if(data.find(patternGet) != std::string::npos){
            isGet = true;
        }

     
        if (isGet)
        {
            if (data.find(pattern) != std::string::npos)
            {
                reading = false;
            }
        }

        if(isPost){
            cout << "POST REQUEST NOW" << endl;
        }

        if(data.find(patternPost) != std::string::npos){
            isPost = true;
        }


    }
     allDataBuffer[bufferIndex] = '\0';
     cout << "END-------------------------------------------------------------------------------------------" <<endl;
        // cout << "BUFFER: ---------------------------------- " <<endl << buf1 << endl;

    string finishedData{allDataBuffer};
    cout << "-------------------------------START FINISHED DATA----------------------------------" << endl;

    cout << finishedData << endl;

    cout << "-------------------------------END FINISHED DATA----------------------------------" << endl;

    istringstream requestInfo(finishedData.c_str());
    istringstream *reqPtr = &requestInfo;

    // cout << "------------------REQ:----------------" << endl;
    // cout << data << endl;
    // cout << "------------------REQ:----------------" << endl;

    ostringstream *outputWriter = new ostringstream();
    response = new Response(msgsocket->getSocket(), outputWriter);
    request = new Request(reqPtr);

    UploadServlet *up = new UploadServlet{msgsocket->getSocket()};

    string requestMethod = request->getReqMethod();
    // cout << "METHOD: [" << requestMethod << "]" << endl;

    runMethod(requestMethod, response, request, *up);

    // string locationOfRequest = request -> getUserAgent();

    // if (locationOfRequest == "browser")
    // {
    //     up = (UploadServlet) new UploadServlet();
    // }
    // else if (locationOfRequest == "cli")
    // {
    //     // up = new ClientServlet();
    // }



    // runMethod(requestMethod, response, request, *up);



    // send(msgsocket,get_http, strlen(get_http.c_str()),0 );
   return "";//requestMethod;
}
