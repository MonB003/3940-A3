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
    return send_res;
}

// string ServerThread::readSocket()
// {
//     char character[1];
//     string fileData;
//     int r;

//     cout << "START OF READSOCKET LOOP" << endl;

//     while (r = recv(msgsocket->getSocket(), &character, 1, 0) == 1)
//     {
//         cout << *character << endl;
//         fileData += *character;
//         // cout << "R VAL: " << r << endl;
//     }

//     //     char* requestPtr = (char*)malloc(fileData.length() + 1);
//     //     char arr[fileData.length()];
//     //     strcpy(arr, fileData.c_str());

//     //   //  cout << "FILE DATA LOOP" << endl;
//     //     for(int i = 0; i < fileData.length(); i++){
//     //         requestPtr[i] = arr[i];
//     //   //      cout << "file character: " << requestPtr[i] <<endl;;

//     //     }

//     // requestPtr[fileData.length()] = '\0';
//     // cout<<"---------------------------------------"<<endl;
//     // cout << requestPtr << endl;

//     return fileData;
// }

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
        cout << "server is doing post req....." << endl;
        up.post(*res, *req);
        
        
        up.get(*res, *req);
    }
}

string ServerThread::run()
{
    int bufferSize = 1;
    char buf[bufferSize];
    string boundaryCode = "";
    char allDataBuffer[1024 * 1024];
    int i = 0;
    int rval;
    string patternGet = "GET";
    string patternPost = "POST";
    string patternBoundary = "WebKitFormBoundary";
    string pattern = "\r\n\r\n";
    string boundary = "boundary=---------------------------";
    string findBoundaryPattern = "";

    char buf2[526336];
    bool checkBoundary = false;
    int j = 0;

    bool isGet = false;
    bool isPost = false;
    bool firstChar = true;

    bool startByteCode = false;
    bool endByteCode = false;
    string boundaryCheckString = "";
    int bufferIndex = 0;
    bool haveCode = false;

    while (rval = read(msgsocket->getSocket(), buf, bufferSize) == 1)
    {

        allDataBuffer[bufferIndex] = *buf;
        string data{allDataBuffer};
        bufferIndex++;

        // each line of the request.
        if (*buf == '\n')
        {
            // cout << "LINE: " << data << endl;
        }

        if (data.find(patternGet) != std::string::npos)
        {
            isGet = true;
        }

        if (isGet)
        {
            if (data.find(pattern) != std::string::npos)
            {
                break;
            }
        }

        if (isPost)
        {
            //  cout << "POST REQUEST NOW" << endl;
        }

        if (data.find(patternPost) != std::string::npos)
        {
            isPost = true;
            // cout << "POST FOUND" << endl;
        }

        if (data.find(boundary) != std::string::npos)
        {
            cout << "FOUND BOUNDARY" << endl;
            if (!firstChar && !haveCode)
            {
                if (isdigit(*buf))
                {
                    boundaryCode += *buf;
                    cout << "BOUNDARY CODE: " << boundaryCode << endl;
                }
                else
                {
                    findBoundaryPattern += boundaryCode + "--";
                    cout << "\n\n--------The final boundary pattern: " << findBoundaryPattern << "\n\n"
                         << endl;
                    haveCode = true;
                }

                cout << "end of code" << endl;
            }
            else
            {
                firstChar = false;
            }
        }

        if (haveCode && data.find(findBoundaryPattern) != std::string::npos)
        {
            cout << "WE ARE DONE" << endl;
            break;
        }
    }

    allDataBuffer[bufferIndex] = '\0';
    cout << "END-------------------------------------------------------------------------------------------" << endl;
    // cout << "BUFFER: ---------------------------------- " <<endl << buf1 << endl;

    string finishedData{allDataBuffer};
    cout << "-------------------------------START FINISHED DATA----------------------------------" << endl;

    cout << finishedData << endl;




    cout << "POST IS: " << isPost << endl;

    if (isPost) {
        writeFile(finishedData);
    }
    



    cout << "-------------------------------END FINISHED DATA----------------------------------" << endl;

    cout << "-----------1-------------" << endl; 
    istringstream requestInfo(finishedData.c_str());
        cout << "-----------2-------------" << endl; 

    istringstream *reqPtr = &requestInfo;
        cout << "-----------3-------------" << endl; 

    ostringstream *outputWriter = new ostringstream();
        cout << "-----------4-------------" << endl; 

    response = new Response(msgsocket->getSocket(), outputWriter);
        cout << "-----------5-------------" << endl; 

    request = new Request(reqPtr);
        cout << "-----------6-------------" << endl; 


    UploadServlet *up = new UploadServlet{msgsocket->getSocket()};

    string requestMethod = request->getReqMethod();
    // cout << "METHOD: [" << requestMethod << "]" << endl;
        cout << "-----------6-------------" << endl; 

    runMethod(requestMethod, response, request, *up);
    cout << "-----------7-------------" << endl; 

    // string locationOfRequest = request -> getUserAgent();

    // if (locationOfRequest == "browser")
    // {
    //     up = (UploadServlet) new UploadServlet();
    // }
    // else if (locationOfRequest == "cli")
    // {
    //     // up = new ClientServlet();
    // }

    return ""; // requestMethod;
}












void ServerThread::writeFile(string content) {
        cout << "WRITE FILE" << endl;
        // FILE *filePointer = nullptr;
        // char *test = "test.txt";

        // char buffer[1];

        // filePointer = fopen(test, "w");

        cout << "OPEN FILE" << endl;


       

        // int num;
        // while (1) {
        //      cout << "IN LOOP" << endl;
        //     num = recv(msgsocket->getSocket(), buffer, 1, 0);

        //     cout << "RECEIVE" << endl;
        //     if (num <= 0) {
        //          cout << "NUM IS 0" << endl;
        //         break;
        //     }
        //      cout << "AFTER IF" << endl;
        //     fprintf(filePointer, "%s", content);

        //     cout << "AFTER WRITE" << endl;

        //     bzero(buffer, content.length());
        // }


        fstream myfile;
        myfile.open("test.txt");
        
        bool isTrue = true;

        while (isTrue == true) {
            cout << "WHILE LOOP" << endl;
            cout << content << endl;
            int find1 = content.find("name=\"fileName\";");
            string substr1 = content.substr(find1, content.length());
            int find2 = substr1.find("\r\n");
            string substr2 = substr1.substr(find2, content.length());

            cout << "-------------------FOUND FILENAME" << endl;
            cout << substr1 << endl;
            cout << substr2 << endl;

            myfile << substr2 << "\n";

            // if (content.find("name=\"filename\"") != std::string::npos) {
            //     cout << "-------------------FOUND FILENAME" << endl;
            //     cout << content << endl;
            //     if (content.find("\r\n") != std::string::npos) {
                    
            //     }
            // }
        }
        myfile.close();

    }