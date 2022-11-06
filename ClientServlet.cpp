#include "ClientServlet.hpp"
#include "Socket.hpp"

ClientServlet::ClientServlet(){
    
};

void ClientServlet::getUserInput() {
    cout << "Please enter the file path for the image:" << endl;
    cin >> imagePath;
    cout << "Image Path: " << imagePath << endl;

    cout << "Please enter a Keyword for the image:" << endl;
    cin >> MultiKeyword;
    cout << "Keyword: " << MultiKeyword << endl;

    cout << "Please enter a Caption for the image:" << endl;
    cin >> MultiCaption;
    cout << "Caption: " << MultiCaption << endl;
}

void ClientServlet::POSTRequest() {
    // HttpURLConnection conn = null;
    // BufferedReader reader = null;
    string charset = "UTF-8";

    // Assign File w/ imagePath
    DIR *directory;
    directory = opendir(imagePath.c_str());


    // POST Request: Upload an image from File System as "Multipart Data" along with
    // other form data (Date, Keyword, Caption, Filename)
    try {

        // Create Socket Connection to "server" at "portNumber".
        // Socket serverSocket = new Socket(portNumber);

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
        // Files.copy(file, outputStream);
        // outputStream;
        writer.append(newLine);
        // End of Multipart.
        writer.append("--").append(boundary).append("--").append(newLine);

        cout << writer << endl;

        // BufferedReader respnse = new BufferedReader(new InputStreamReader(serverSocket.getInputStream()));

        // serverSocket.close();

    } catch (...) {
        // cout << e << endl;
    }
}


// int main(){
//     ClientServlet *client = new ClientServlet();
//     client->getUserInput();
//     client->POSTRequest();
// }
