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

 if ((rval = write(sock, res, strlen(res))) < 0){
   perror("writing socket");
  }else  {
    
    //printf("%s\n",res);
  //  close(this->sock);
     shutdown(sock, SHUT_WR);

 }

	return;
}
Socket::~Socket()
{
}
