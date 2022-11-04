#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>

using namespace std;



class Request{

    public:
        Request(){};

        Request(istringstream* inStream) {
        inputStream = inStream;
        // Create a method to parse incoming request payload
        parsePayload(inputStream);
    }


    void parsePayload(istringstream* inStream) {
        string savedByteCode = "";

        cout << "PARSE PAYLOAD" << endl;

        //Scanner scanner = new Scanner(inStream);

        /*
        
        
        */

        // Need to know Request type: GET or POST
        // Parse First Line
        // reqType = scanner.next();
        *inStream >> reqType;

        cout << "The Request Type is: " << endl;
        string temp = "";


        string dataKeys[] = {"Date", "Keyword", "Caption", "File"};
        int currentKey = 0;
        int maxKey = 4;
        bool endOfDataReached = false;
        while(!endOfDataReached && currentKey < maxKey) {
            // Print each token.
            // temp = scanner.nextLine();
            *inStream >> temp;
            cout << temp;

            
            // Check and Set User-Agent
            if (temp.find("User-Agent:")){
                reqUserAgent = "browser";
            }
            if (temp.find("User-Agent: cli")){
                reqUserAgent = "cli";
            } 


            if (temp.find("--boundary")) {
                // Start of the current body from the form data
                // string currBody = scanner.nextLine();
                string currBody;
                *inStream >> currBody;

                string currValue = "";

                // Loop until next boundary is reached
                // while (!currBody.trim() == ("")) {
                while (!currBody.empty()) {
                    currValue = currBody;           // Store previous line's value
                    // currBody = scanner.nextLine();  // Get next line
                    *inStream >> currBody;
                    cout << "CURRBODY: " << currBody << endl;
                }

                // currValue = scanner.nextLine();
                *inStream >> currValue;

                // Store value in hashmap
                // FormData.put(dataKeys[currentKey], currValue);
                pair<string, string> currentData = make_pair(dataKeys[currentKey], currValue);
                FormDataMap.insert(currentData);

                cout << "PUT IN MAP: " << dataKeys[currentKey] << ", " << currValue << endl;
                currentKey++;
            }

            if (currentKey == 3 && temp.find("--boundary")){

                // At the File Body Part. Currently at "--boundary"
                // string iterateByteCode = scanner.nextLine();
                string iterateByteCode;
                *inStream >> iterateByteCode;


                // Parse File Body Part..
                while(!(iterateByteCode.empty())) {

                    // Keep iterating until you find empty line, which tells us to start reading at the next line.
                    cout << "NOT AT EMPTY LINE" << iterateByteCode << endl;
                    // iterateByteCode = scanner.nextLine();
                    *inStream >> iterateByteCode;
                }
                // temp = scanner.nextLine();
                *inStream >> temp;
            }

            while ((!temp.empty()) && currentKey == 3 && !(temp == ("--boundary--"))){
                // savedByteCode = savedByteCode + temp;
                savedByteCode.append(temp);

                // temp = scanner.nextLine();
                *inStream >> temp;
            }
            
            if (temp.find("Accept-Language:") || temp.find("--boundary--")){
                cout << "THIS SHOULD BE THE LAST ONE" << endl;
                imageByteCode = savedByteCode;
                endOfDataReached = true;
            }
        }

        // System.out.println("Made it here");
        // scanner.close();
    }





    void setReqType(string reqType) {
        this->reqType = reqType;
    }

    void setUserAgent(string userAgent) {
        reqUserAgent = userAgent;
    }

    string getReqMethod() {
        return reqType;
    }

    string getUserAgent() {
        return reqUserAgent;
    }

    istringstream* getInputStream() {
        return inputStream;
    }

    string getFormData(string key){
        // string found = FormDataMap.find(key);
        return FormDataMap.at(key);
    }

    string getImageByteCode(){
        return imageByteCode;
    }
    

    private:
        istringstream* inputStream;
        string reqType;
        string reqUserAgent;
        unordered_map<string, string> FormDataMap;
        string imageByteCode;
};