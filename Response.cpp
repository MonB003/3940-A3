#include "Response.hpp"

Response::Response(ostringstream *outStreamInput) : outStream(outStreamInput) {}

Response::Response(int socketInput, ostringstream *outStreamInput) : socket(socketInput), outStream(outStreamInput) {}

void Response::sendBack(string page)
{
    ostream *out = getOutputStream();

    // string htmlPage = page;
    // string CRLF = "\r\n"; // need this line
    // string response = "HTTP/1.1 200 OK";
    // response.append(CRLF);
    // response.append("Content-Length: ");
    // stringstream pageLenStream;
    // pageLenStream << htmlPage.length();
    // string pageLength = pageLenStream.str();
    // response.append(pageLength);
    // response.append(CRLF);
    // response.append(CRLF);
    // response.append(htmlPage);
    // response.append(CRLF);
    // response.append(CRLF);

    // out << (response)<<endl; // renders the page.
    string html = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 600\n\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title> File Upload Form</title>\r\n</head>\r\n<body>\r\n<h1>Upload file</h1>\r\n<form id =\"form\" method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n<input type=\"file\" name=\"fileName\"/><br/><br/>\r\nCaption: <input type =\"text\" name=\"caption\"<br/><br/>\r\n <br/>\nDate : <input type=\"date\" name=\"date\"<br/><br/>\r\n <br/>\n <input id='formBtn' type=\"submit\" name=\"submit\" value=\"Submit\"/>\r\n </form>\r\n</body>\r\n</html>\r\n";

    char arr[200] = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 16\n\n<h1>testing</h1>";
    int send_res = send(socket, html.c_str(), html.length(), 0); //
                                                                    // do a response...
                                                                    // return send_res;
}

void Response::createHeader()
{
    time_t ttime = time(0);
    char *dt = ctime(&ttime);
    string headerString = "GET / HTTP/1.1 OK\r\nDate: ";
    headerString.append(dt);
    headerString.append("\r\nContent-Type: ");
    headerString.append(contentType);
    headerString.append("\r\n");
    headerString.append("Character-Encoding:");
    headerString.append(characterEncoding);
    headerString.append("\r\n");
    *outStream << headerString;
}