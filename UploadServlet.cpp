#include "UploadServlet.hpp"

// UploadServlet::UploadServlet(const UploadServlet &up){
//     swap(*this,up);
// }

// g++ main.cpp ServerThread.cpp Request.cpp ServerSocket.cpp Response.cpp Socket.cpp UploadServlet.cpp base64.cpp -o server

UploadServlet::UploadServlet(int socket) : socket(socket) {}

int UploadServlet::getSocket()
{
    return socket;
}

void UploadServlet::post(Response &response, Request &request)
{
    cout << "Start of post uploadservlet ------------------" << endl;
    time_t timer;
    struct tm y2k = {0};
    y2k.tm_hour = 0;
    y2k.tm_min = 0;
    y2k.tm_sec = 0;
    y2k.tm_year = 100;
    y2k.tm_mon = 0;
    y2k.tm_mday = 1;
    long seconds;

    time(&timer);
    seconds = difftime(timer, mktime(&y2k));

    string filename = "./images/";

    string timeString = to_string(seconds);

    // filename.append(seconds);
    filename.append(timeString);
    filename.append(".png");
    // may need to set write mode to base64 if we end up doing that again, not totally sure how
    ofstream fileOut(filename, ios_base::out | ios_base::binary);
    cout << "Opened file stream -----------" << endl;
    // Base64 Encoder doesnt workkk.
    string byteStr = "iVBORw0KGgoAAAANSUhEUgAAAB8AAAARCAYAAAAlpHdJAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAAAC2SURBVEhL7ZXdDYMwDIS9YCTmQdnETBLm4CFTeIRrapLGRakQLTQP7cNJsXz4u/xIkIigl34YzgPBTbHZPKTZg8gjtHovdA18YThy4GXj2eg8uNUxOMMTpeRJAyMWQ94NT27tJflZEMbszbX1Bgl11k4AhVdThNZjWA06sJ5MzCEKUEOUsO8e+wN2lx1i141aw3wKf7pz/bAX3A75BrwObN35xfC9134YXjZhHmdL/x9LF3WEC25pAgP+h75e8AAAAABJRU5ErkJggg==";
    cout << byteStr << endl;
    cout << "Got image bytecode ---------------" << endl;
    string base64Str = base64_decode(byteStr);
    cout << "Decoded bytecode ------------------" << endl;
    fileOut << base64Str;
    cout << "Placed bytecode ------------------" << endl;
    fileOut.write(base64Str.c_str(), base64Str.length());
    fileOut.close();

    DIR *directory;
    struct dirent *currFile;
    directory = opendir("./images"); // Gets all files in the images folder
    vector<string> fileNames;
    if (directory)
    {
        while ((currFile = readdir(directory)) != nullptr)
        {
            fileNames.push_back(currFile->d_name);
        }
    }
    sort(fileNames.begin(), fileNames.end());
    int i = 1;
    for (string str : fileNames)
    {
        cout << "Image " << i << ": " << str << endl;
        i++;
    }
    closedir(directory);
}

string UploadServlet::get(Response &response, Request &request)
{
    string html = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 600\n\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title> File Upload Form</title>\r\n</head>\r\n<body>\r\n<h1>Upload file</h1>\r\n<form id =\"form\" method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n<input type=\"file\" name=\"fileName\"><br/><br/>\r\nCaption: <input type =\"text\" name=\"caption\"><br/><br/>\r\n <br/>\nDate : <input type=\"date\" name=\"date\"><br/><br/>\r\n <br/>\n <input id='formBtn' type=\"submit\" name=\"submit\" value=\"Submit\">\r\n </form>\r\n</body>\r\n</html>\r\n";
   // int send_res = send(socket, html.c_str(), html.length(), 0);

  //  int rval = write(socket,html.c_str(),html.length());

//    shutdown(socket, SHUT_WR);
    return html;
}

string UploadServlet::getListing()
{
    string dirList = "<!DOCTYPE html>\r\n<html>\r\n<body>\r\n<ul>";
    DIR *directory;
    struct dirent *currFile;
    directory = opendir("./images"); // Gets all files in the images folder
    if (directory)
    {
        while ((currFile = readdir(directory)) != nullptr)
        {
            cout << currFile->d_name << endl;
            dirList.append("<li>");
            dirList.append(currFile->d_name);
            dirList.append("</li>");
            dirList.append("<br>");
        }
    }
    closedir(directory);

    dirList.append("</ul></body></html>");

    return dirList;
}