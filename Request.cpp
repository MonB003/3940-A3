#include "Request.hpp"

Request::Request(){};

Request::Request(istringstream *inStream)
{
    inputStream = inStream;
    parsePayload(inputStream);
    // parsePayload2(inputStream);
    FormDataMap = map<string,string>();
}

void Request::loopLine(string line, map<string, string> FormDataMap)
{
    auto it = line.begin();
    string key = "";
    string value = "";
    bool flag = false;

    while (it != line.end())
    {
        if ((*it == ':' || *it == '/') && !flag)
        {
            it++;
            flag = true;
        }
        else
        {
            if (flag)
            {
                if (*it == '\r' || *it == '\n')
                {
                    break;
                }
                else
                {
                    value += *it;
                }
            }
            else
            {
                key += *it;
                if (key == "GET")
                {
                    reqType = "GET";
                    key = "Request";
                    value = "GET";
                    break;
                }
            }
        }
        it++;
    }

    //auto pair = make_pair(key, value);
    FormDataMap.insert({key,value});
    //FormDataMap.insert(pair);    

}

string Request::getReqMethod()
{

    cout << "in map" << endl;

    auto it = FormDataMap.begin();

    while(it != FormDataMap.end()){
        cout << "first: " << it->first <<endl;
        cout<< "second: " << it->second << endl; 
        it++;

    }

    // auto pair = FormDataMap.find("Request");
    // string request = pair->second;
    // cout << "Request type: " <<request << endl;

    return reqType;
}

void Request::parsePayload(istringstream *inStream)
{
    string savedByteCode = "";
    string temp = "";
    string dataKeys[] = {"Date", "Keyword", "Caption", "File"};
    int currentKey = 0;
    int maxKey = 4;
    bool endOfDataReached = false;
    int totalLengthOfPayload = 0;

    while (*inStream >> temp)
    {
        totalLengthOfPayload += temp.size();
    }

    cout << "Temp size: " << totalLengthOfPayload << endl;

    int currentLength = 0;
    inStream->clear();
    inStream->seekg(0);

    string requestType;

    string title;
    string value;

    char c;
    string line;

    while (getline(*inStream, line))
    {

        loopLine(line, FormDataMap); // loops each line and parses it into a pair.

        int tokenLength = temp.size();

        if (temp.find("User-Agent:"))
        {
            reqUserAgent = "browser";
        }

        if (currentLength == totalLengthOfPayload)
        {
            break;
        }

        currentLength += tokenLength;
    }
}




void Request::parsePayload2(istringstream* inStream){
        cout << "Parsing Payload" << endl;
        string intermediate;
        string reqType;
        string boundary;
        string userAgent;
        string caption;
        string date;
        while (*inStream >> intermediate){
            cout << intermediate << endl;

            if(intermediate.find("POST") != std::string::npos){
                cout << intermediate << endl;
                reqType = intermediate;
            }
            if(intermediate.find("boundary=") != std::string::npos){
                cout << intermediate << endl;
                boundary = intermediate;
            }
            if(intermediate.find("User-Agent:") != std::string::npos){
                *inStream >> intermediate;
                cout << intermediate << endl;
                userAgent = intermediate;

            }
            if(intermediate.find("name=\"caption\"") != std::string::npos){
                *inStream >> intermediate;
                cout << intermediate << endl;
                caption = intermediate;

            }
            if(intermediate.find("name=\"date\"") != std::string::npos){
                *inStream >> intermediate;
                cout << intermediate << endl;
                date = intermediate;

            }
        }
        boundary = "--" + boundary.substr(9,boundary.length());
        cout << "RequestType: " << reqType << endl;
        cout << "Boundary: " << boundary << endl;
        cout << "UserAgent: " << userAgent << endl;
        cout << "Caption: " << caption << endl;
        cout << "Date: " << date << endl;
    }