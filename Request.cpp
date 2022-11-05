#include "Request.hpp"

Request::Request(){};

Request::Request(istringstream *inStream)
{
    inputStream = inStream;
    // Create a method to parse incoming request payload
    parsePayload(inputStream);
}

void Request::loopLine(string line, multimap<string, string> FormDataMap)
{
    auto it = line.begin();
    string key = "";
    string value = "";
    bool flag = false;
    while (it != line.end())
    {
        if ((*it == ':'|| *it == '/') && !flag)
        {
            it++;
            flag = true;

        }
        else
        {
            if (flag)
            {
                if(*it == '\r' || *it == '\n'){
                    break;
                } else {
                value += *it;
                }
            }
            else
            {
                key += *it; 
                if(key == "GET"){
                    key ="Request";
                    value = "GET";
                    break;
                }
            }
        }

        it++;
    }

    cout << "Key [" <<key<<"]" <<endl;
    cout << "Val: [" <<value <<"]"<<endl;
    auto pair = make_pair(key,value);
    FormDataMap.insert(pair);
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
  

    // istringstream iss(line);

    // string url;
    // string version;
    // iss >> reqType;
    // cout <<"the request is: " << line <<endl;
    // iss >> url;
    // iss >> version;
    // string reqType;
    //   getline(*inStream, reqType);
    //     cout <<"the request is: " << reqType <<endl;



    // *inStream >> url;
    // *inStream >> version;

    while (getline(*inStream, line))
    {

        cout << "LINE: " << line << endl;

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

    cout << "USER AGENT:   " << reqUserAgent << endl;

    cout << "WERE FREEEEEE" << endl;

    auto it = FormDataMap.begin();

    while (it != FormDataMap.end())
    {

        cout << "FIRST: " << it->first << endl;

        cout << "SECOND: " << it->second << endl;
        it++;
    }
}