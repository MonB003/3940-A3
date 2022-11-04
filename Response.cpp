#include "Response.hpp"


Response::Response(ostringstream *outStreamInput):outStream(outStreamInput){}

Response::Response(Socket socketInput, ostringstream *outStreamInput):socket(socketInput),outStream(outStreamInput){}

void Response::send(string page){
  ostream* out = getOutputStream();
            string htmlPage = page;
            string CRLF = "\r\n"; // need this line
            string response = "HTTP/1.1 200 OK";
            response.append(CRLF);
            response.append("Content-Length: ");
            stringstream pageLenStream;
            pageLenStream << htmlPage.length();
            string pageLength = pageLenStream.str();
            response.append(pageLength);
            response.append(CRLF);
            response.append(CRLF);
            response.append(htmlPage);
            response.append(CRLF);
            response.append(CRLF);

              //out << response; // renders the page.
}