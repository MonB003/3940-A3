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

string ServerThread::runMethod(string &method, Response *res, Request *req, Servlet &up)
{
    string responseStr;

    if (method == "GET")
    {
        responseStr = up.get(*res, *req);
    }
    else
    {
        up.post(*res, *req);
        responseStr = "HTTP/1.1 200 OK\nContent-Type:text/html\r\n\r\n";
       
        string listfiles = UploadServlet::getListing();
        responseStr.append(listfiles);
    }

    return responseStr;
}

char * ServerThread::run()
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
            cout << "LINE: " << data << endl;
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

    string finishedData{allDataBuffer};
    cout << "-------------------------------START FINISHED DATA----------------------------------" << endl;
    cout << finishedData << endl;
    cout << "-------------------------------END FINISHED DATA----------------------------------" << endl;

    istringstream requestInfo(finishedData.c_str());

    istringstream *reqPtr       = &requestInfo;
    ostringstream *outputWriter = new ostringstream();
    response                    = new Response(msgsocket->getSocket(), outputWriter);
    request                     = new Request(reqPtr);
    UploadServlet *up           = new UploadServlet{msgsocket->getSocket()};
    string requestMethod        = request->getReqMethod();
    string responseStr          = runMethod(requestMethod, response, request, *up);
    char *resPtr                = const_cast<char *>(responseStr.c_str());

    return resPtr ;
}
