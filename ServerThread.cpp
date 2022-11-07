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
    // char buffer[1024 * 1024];
    cout << "here" << endl;
    // string data = readSocket();
    //  renderHTML();

    char buf1[526336];
    char buf[1];
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
    bool dontHaveBoundaryNumber = true;
    bool dontHaveContentLength = false;
    bool numberLength = false;
    char imageByteCode[526336];
    int byteCodeIndex = 0;

    string b = "";

    // istringstream iss(b);
    string boundaryNumber ="" ;
    string contentLengthNumber = "";

    while (((rval = read(msgsocket->getSocket(), buf, 1)) == 1))
    {
        b += *buf;

        if (checkBoundary == true)
        {
            buf2[j] = *buf;
            j++;
        }

        if (b.find(patternGet) != std::string::npos)
        {
            isGet = true;
        }

        if (b.find(patternPost) != std::string::npos)
        {
            isPost = true;

            // cout << "--------------------------------------------POST IS HAPPENING --------------------------------------------" << endl;
        }

        if (isGet)
        {
            if (b.find(pattern) != std::string::npos)
            {
                cout << "BREAKING THE LOOP" << endl;
                break;
            }
        }

        if (b.find("Content-Type: image/") != std::string::npos)
        {
            startByteCode = true;
        }

        if ((b.find("boundary=---------------------------") != std::string::npos) && (isPost == true))
        {
            // 1. until we see whitespace we scan get the boubndary number

            if(*buf =='\n' && !dontHaveContentLength){
                //cout << "\nFINISHED STRING: " << boundaryNumber << "\n\n" << endl;
               dontHaveBoundaryNumber = false;
               dontHaveContentLength = true;
                // do some sort of buffer move
            } else {
                if(dontHaveBoundaryNumber) {
                    boundaryNumber += *buf;
                    // cout << "\nFROM ISS: " << boundaryNumber << "\n\n" << endl;
                } 

                // 2. scan again until end of content length str to know size of body
                  // DONE 
                if(dontHaveContentLength){
                    if(*buf == ' '){
                        
                        contentLengthNumber += *buf;
                        cout << "\nFROM ISS: " << boundaryNumber << "\n\n" << endl;
                        numberLength = true;
                        // add to our new content length
                    } else {
                        if(numberLength){
                            if(*buf == '\n'){
                                cout << "\n\n\n\n-----------------------------------------------------------------CONTENT LENGTH NUMBER: [" << contentLengthNumber <<"]"<< endl;
                                numberLength = false;
                            } else {
                            
                            
                                contentLengthNumber += *buf;
                                // cout << "CONTENT AS WE BUILD:  " << contentLengthNumber << endl;
                            }   
                        }
                    }
                }
            }
                       
            // 3. we want to skip ahead until we hit the other boundary with the -- at the end of our number var.
            // OR until we see the string name="submit" ???

            // cout << "\n--------------------------------------here" << endl;
            imageByteCode[byteCodeIndex] = *buf;
            cout << "next char: " << *buf << endl;
            byteCodeIndex++;
            // cout << imageByteCode[byteCodeIndex];
            b = (string)buf1;
            //  b += *buf1;
        }
        else
        {
            buf1[i] = *buf;

            i++;
            cout << *buf;
            b = (string)buf1;
        }
    }
    buf[i] = '\0';










    




    

    cout << "BUF 2: " << buf2 << endl;

    string data = buf1;
    istringstream requestInfo(data.c_str());
    istringstream *reqPtr = &requestInfo;

    cout << "------------------REQ:----------------" << endl;
    cout << data << endl;
    cout << "------------------REQ:----------------" << endl;

    ostringstream *outputWriter = new ostringstream();
    response = new Response(msgsocket->getSocket(), outputWriter);
    request = new Request(reqPtr);

    UploadServlet *up = new UploadServlet{msgsocket->getSocket()};

    string requestMethod = request->getReqMethod();
    // cout << "METHOD: [" << requestMethod << "]" << endl;

    runMethod(requestMethod, response, request, *up);

    return requestMethod;
}
