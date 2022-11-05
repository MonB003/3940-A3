#include "Request.hpp"

Request::Request(){};

Request::Request(istringstream *inStream){
    inputStream = inStream;
    // Create a method to parse incoming request payload
    parsePayload(inputStream);
}

void Request::parsePayload(istringstream *inStream)
{
    string savedByteCode = "";

    cout << "PARSE PAYLOAD" << endl;
    cout << "The Request Type is: " << endl;
    string temp = "";
    string dataKeys[] = {"Date", "Keyword", "Caption", "File"};
    int currentKey = 0;
    int maxKey = 4;
    bool endOfDataReached = false;
    char c;
    int totalLengthOfPayload = 0;
    
    while (*inStream >> temp){
        totalLengthOfPayload += temp.size();
    }

    cout << "Temp size: " << totalLengthOfPayload << endl;

    int currentLength = 0;
    inStream->clear();
    inStream->seekg(0);

    int index = 0;
    string requestType;

    string title;
    string value;

    string url;
    string version;
    *inStream >> reqType;
    *inStream >> url;
    *inStream >> version;

    while (*inStream >> temp)
    {

        if (index % 2 == 0)
        {
            title = temp;
            cout << "VAR TITLE: " << title << endl;
        }
        else
        {
            value = temp;
            cout << "VALUE: " << value << endl;

            pair<string, string> currentData = make_pair(title, value);
            FormDataMap.insert(currentData);
        }

        index++;
        int tokenLength = temp.size();
        //     cout << "TOKEN: " << temp <<"------------------" <<endl;

        if (temp.find("User-Agent:"))
        {

            reqUserAgent = "browser";
            // cout << "BROWSER FOUND" << endl;
        }

        if (currentLength == totalLengthOfPayload)
        {
            break;
        }

        currentLength += tokenLength;
    }

    cout << "USER AGENT:   " << reqUserAgent << endl;

    cout << "WERE FREEEEEE" << endl;

    auto it = FormDataMap.begin();

    while (it != FormDataMap.end())
    {   
        
        cout << "FIRST: " << it->first << endl;

        cout <<"SECOND: " <<  it->second << endl;
        it++;
    }
}