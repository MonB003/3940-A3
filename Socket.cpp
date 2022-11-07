#include "Socket.hpp"

Socket::Socket(int sock)
{
	this->sock = sock;
}
string Socket::getRequest()
{
  int rval;
  char buffer[1024 * 1024];

  recv(sock, &buffer, 1024 * 1024, 0);
  
  cout <<"buffer sending back..." <<endl;
  cout << "buff: " << buffer << endl;



	return buffer;
}

void Socket::sendResponse(char *res){
int rval;
    char* html = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 600\n\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title> File Upload Form</title>\r\n</head>\r\n<body>\r\n<h1>Upload file</h1>\r\n<form id =\"form\" method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n<input type=\"file\" name=\"fileName\"><br/><br/>\r\nCaption: <input type =\"text\" name=\"caption\"><br/><br/>\r\n <br/>\nDate : <input type=\"date\" name=\"date\"><br/><br/>\r\n <br/>\n <input id='formBtn' type=\"submit\" name=\"submit\" value=\"Submit\">\r\n </form>\r\n</body>\r\n</html>\r\n";


 if ((rval = write(sock, res, strlen(res))) < 0){
   perror("writing socket");
  }else  {
    
      printf("%s\n",res);
     shutdown(sock, SHUT_WR);

 }

	return;
}
Socket::~Socket()
{
}
