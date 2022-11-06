#include "Socket.hpp"

Socket::Socket(int sock)
{
	this->sock = sock;
}


string Socket::getRequest()
{
  int rval;
  int totalSize = 0;
  char buffer[1024 * 1024];
  char buf[1];
  int count;
  int i = 0;

 // recv(sock, &buffer, 1024 * 1024, 0);

  while(count = recv(sock, &buf, 1, 0) > 0){

    buffer[i] = *buf;
    cout << "character: " << *buf << endl;
    totalSize += count;
  
    if(count == -1){
      perror("error:");
    } else if(count == 0){
      break;
    }
    i++;
  }
  
  cout <<"buffer sending back..." <<endl;
  cout << "buff: " << buffer << endl;

	return buffer;
}

void Socket::sendResponse(char *res){
int rval;

  if ((rval = write(sock, res, strlen(res))) < 0){
    perror("writing socket");
  }else  {
    
    printf("%s\n",res);
    //close(this->sock);
  }

	return;
}
Socket::~Socket()
{
}
