#include "UploadServlet.hpp"

// UploadServlet::UploadServlet(const UploadServlet &up){
//     swap(*this,up);
// }

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
    string byteStr = request.getImageByteCode();
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

int UploadServlet::get(Response &response, Request &request)
{
    string html = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 600\n\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title> File Upload Form</title>\r\n</head>\r\n<body>\r\n<h1>Upload file</h1>\r\n<form id =\"form\" method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n<input type=\"file\" name=\"fileName\"/><br/><br/>\r\nCaption: <input type =\"text\" name=\"caption\"<br/><br/>\r\n <br/>\nDate : <input type=\"date\" name=\"date\"<br/><br/>\r\n <br/>\n <input id='formBtn' type=\"submit\" name=\"submit\" value=\"Submit\"/>\r\n </form>\r\n</body>\r\n</html>\r\n";
   // int send_res = send(socket, html.c_str(), html.length(), 0);

    int rval = write(socket,html.c_str(),html.length() );
    // if (send_res != -1)
    // {
    //     cout << "spot 1" << endl;
    //     char szBuffer[10000 + 1];
    //     cout << "spot 2" << endl;

    //     send_res = recv(socket, szBuffer, 10000+1, 0);
    //     cout << "spot 3" << endl;

    //     if (send_res > 0)
    //     {
    //         // safely null terminate
    //         szBuffer[send_res] = '\0';
    //         cout << "RECEIVE: " << szBuffer << endl;
    //     }
    // }
    return rval;
}

string UploadServlet::getListing()
{
    string dirList = "<ul>";
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
        }
    }
    closedir(directory);

    dirList.append("</ul>");

    return dirList;
}