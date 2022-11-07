#include "ClientServlet.hpp"
#include "Socket.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

// g++ ClientServlet.cpp Socket.cpp base64.cpp -o client
// C:\Users\super\OneDrive\Desktop\Emotes\bmit.PNG

ClientServlet::ClientServlet(){

};

void ClientServlet::getUserInput() {
    cout << "Please enter the file path for the image:" << endl;
    cin >> imagePath;
    cout << "Image Path: " << imagePath << endl;

    cout << "Please enter a date for the image:" << endl;
    cin >> MultiDate;
    cout << "Date: " << MultiDate << endl;

    cout << "Please enter a Keyword for the image:" << endl;
    cin >> MultiKeyword;
    cout << "Keyword: " << MultiKeyword << endl;

    cout << "Please enter a Caption for the image:" << endl;
    cin >> MultiCaption;
    cout << "Caption: " << MultiCaption << endl;
}

string ClientServlet::encodeImage(string imagepath){
    ifstream image;
    image.open(imagePath, ios::binary);
    
    string imageBytes;
    string temp;
    while(image >> temp){
        imageBytes.append(temp);
    }
    imagebase64 = base64_encode(imageBytes);
    return imagebase64;
}

void ClientServlet::POSTRequest() {
    // HttpURLConnection conn = null;
    // BufferedReader reader = null;
    string charset = "UTF-8";

    // Assign File w/ imagePath
    DIR *directory;
    directory = opendir(imagePath.c_str());

    ifstream image;
    image.open(imagePath, ios::binary);
    
    string imageBytes;
    string temp;
    
    while(image >> temp){
        imageBytes.append(temp);
    }
    string imageBase64 = encodeImage(imageBytes);
    cout << "ByteCode:\n" << imageBase64 << endl;

    // POST Request: Upload an image from File System as "Multipart Data" along with
    // other form data (Date, Keyword, Caption, Filename)
    try {
        /*
        // ================ socketclient.cc =================================
        int sock;
        // sockaddr_in is a struct that specifies a Transport Address and Port for the AF_INET Address Family
        struct sockaddr_in server;
        char buf[1024];
        // hostent is a struct that describes the Internet Host.
        struct hostent *hp;
        // Host IP Address
        char *host = "127.0.0.1";
        // Return Value - Flag for ....
        int rval;

        // Creates an Endpoint for communication and returns a File Descriptor that refers to that endpoint.
        // On success, a File Descriptor for the new Socket is returned. On error -1 is returned, and errno is set to indicate the error.
        sock = socket (AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            // perror() produces a message on standard error describing the last error encountered.
            perror("opening stream socket");
        }

        // Erases the data in the n bytes of the memory starting at the location pointed.
        bzero(&server, sizeof(server));
        // gethostbyname() returns a structure of type hostent for the given host name. "localhost:8888" - "hostname:portnumber"
        hp = gethostbyname("localhost");
        // bcopy() copies n bytes from src to dest. (src, dest, size)
        // Ultimately, is using hostent (hp) to set our server address for the Socket to connect to.
        bcopy((char*)hp->h_addr, (char*)&server.sin_addr, hp->h_length);
        //Set connection type to Internet
        server.sin_family = AF_INET;
        //Set port to our port number
        server.sin_port = portNumber;
        
        // Use Socket to connect Server Address.
        if (connect(sock, (struct sockaddr*)&server, sizeof(server))<0){
            perror("connecting");
        }
        
        // Copies string into buffer
        strcpy(buf,"/usr/include");
        // Write to File Descriptor (File Descriptor, Input, Input Size)
        // On success the number of bytes written is returned. On error, -1 is returned
        if ((rval = write(sock, buf, 1024)) < 0){
            // Print if error.
            perror("writing socket");
        }
        // Read from File Descriptor (File Descriptor, output, output Size)
        // On success the number of bytes written is returned. On error, -1 is returned. Zero indicates end of file.
        if ((rval = read(sock, buf, 1024)) < 0){
            // Print if error.
            perror("reading socket");
        }

        // printf("%s\n", buf);
        cout << buf << endl;

        // Closes a File Descriptor, so that it no longer refers to any file and may be reused.
        close (sock);

        // ================ socketclient.cc =================================
        // ================ socketserver.cc =================================

        int sock, length;
        // Sockaddr_in is a struct that Specifies a Transport Address and Port 
        struct sockaddr_in server;
        int msgsock;
        char buf[1024];
        int rval;
        int i;
        
        // Creates an File Descriptor that points at an endpoint for communication. - Returns a File Descriptor.
        sock = socket (AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("opening stream socket");
        }
        
        server.sin_family = AF_INET;
        // sin_addr is the IP address in the socket
        // INADDR_ANY is used when we don't want to bind a socket to any specific IP.
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = 8888;
        
        // bind(File Descriptor, Socket Address, sizeof Socket Address)
        // Binds the Server to the File Descriptor.
        // On Success, zero is returned. On error, -1 is returned, and errno is set to indicate error.
        if (bind (sock, (struct sockaddr *)&server, sizeof server) < 0) {
            perror ("binding stream socket");
        }
        //Used to specify that this socket will be used to accept connections, and how many connections it will allow at a time
        listen (sock, 5);
        // Accept(File Descriptor, sockaddr, socklength)
        // Returns a File Descriptor to deal with each incoming socket connection that 'sock' is listening to.
        msgsock = accept(sock, (struct sockaddr *)0, (socklen_t *)0);
        if (msgsock == -1) {
            perror("accept");
        }
        // Read from msgsock 'file descriptor' and puts it into the output 'buffer', at size of (1024) characters.
        if ((rval = read(msgsock, buf, 1024)) < 0){
            perror("reading socket");
        }else  {
            printf("%s\n",buf);
        }
        // Closes the 'Inner file descriptor'
        close (msgsock);
        
        // ================ socketserver.cc =================================*/




        int sock;
        struct sockaddr_in server;
        char buf[1024];
        struct hostent *hp;
        char *host = "127.0.0.1";
        int rval;

        sock = socket (AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Error opening stream socket");
        }

        // Erases the data in the n bytes of the memory starting at the location pointed.
        bzero(&server, sizeof(server));
        // gethostbyname() returns a structure of type hostent for the given host name. "localhost:8888" - "hostname:portnumber"
        hp = gethostbyname("localhost");
        // bcopy() copies n bytes from src to dest. (src, dest, size)
        // Ultimately, is using hostent (hp) to set our server address for the Socket to connect to.
        bcopy((char*)hp->h_addr, (char*)&server.sin_addr, hp->h_length);
        //Set connection type to Internet
        server.sin_family = AF_INET;
        //Set port to our port number
        server.sin_port = htons(portNumber);
        
        // Use Socket to connect Server Address.
        if (connect(sock, (struct sockaddr*)&server, sizeof(server))<0){
            perror("Error connecting");
        }

        cout << "socket int:  " << sock 

        // Get OutputStream for Socket
        // OutputStream outputStream = serverSocket.getOutputStream();

        // Create PrintWriter for output capabilities to Server
        // PrintWriter writer = new PrintWriter(new OutputStreamWriter(outputStream, charset));
        string writer;

        // Define and open connection to URL.
        // URL url = new URL("http://localhost:8081/Client-Server-A1b/upload");
        // conn = (HttpURLConnection) url.openConnection();
        string boundary = "boundary";
        string payload = "";
        string newLine = "\r\n";

        // Set output capability to true
        writer.append("POST / HTTP/1.1").append(newLine);
        writer.append("Content-Type: multipart/form-data; boundary=").append(boundary).append(newLine);
        writer.append("User-Agent: cli").append(newLine).append(newLine);

        // Sending text "Data"
        writer.append("--").append(boundary).append(newLine);
        writer.append("Content-Disposition: form-data; name=\"Date\"").append(newLine);
        writer.append("Content-Type: text/plain; charset=").append(charset).append(newLine);
        writer.append(newLine).append(MultiDate).append(newLine);

        // Sending text "Keyword"
        writer.append("--").append(boundary).append(newLine);
        writer.append("Content-Disposition: form-data; name=\"Keyword\"").append(newLine);
        writer.append("Content-Type: text/plain; charset=").append(charset).append(newLine);
        writer.append(newLine).append(MultiKeyword).append(newLine);

        // Sending text "Caption"
        writer.append("--").append(boundary).append(newLine);
        writer.append("Content-Disposition: form-data; name=\"Caption\"").append(newLine);
        writer.append("Content-Type: text/plain; charset=").append(charset).append(newLine);
        writer.append(newLine).append(MultiCaption).append(newLine);

        // Sending Image File
        writer.append("--").append(boundary).append(newLine);
        writer.append("Content-Disposition: form-data; name=\"File\"; ").append("filename=\"").append("somethinghere").append("\"").append(newLine);
        writer.append("Content-Type: image/png").append(newLine);
        writer.append("Content-Transfer-Encoding: binary").append(newLine);
        writer.append(newLine);
        writer.append(imageBase64);
        writer.append(newLine);
        // End of Multipart.
        writer.append("--").append(boundary).append("--").append(newLine);

        cout << writer << endl;

        // BufferedReader respnse = new BufferedReader(new InputStreamReader(serverSocket.getInputStream()));

        // serverSocket.close();

        // Copies string into buffer
        // strcpy(buf,"/usr/include");
        // Write to File Descriptor (File Descriptor, Input, Input Size)
        // On success the number of bytes written is returned. On error, -1 is returned
        if ((rval = write(sock, "hello world!!!", 1024)) < 0){
        // if ((rval = write(sock, writer.c_str(), writer.length())) < 0){
            // Print if error.
            perror("Error: Writing to Socket");
        }
        
        close (sock);
    } catch (...) {
        // cout << e << endl;
    }
}


int main(){
    ClientServlet *client = new ClientServlet();
    client->getUserInput();
    client->POSTRequest();
}