#include <iostream>
#include <sstream>

using namespace std;


class Request{

    public:
        Request(){};

        Request(istringstream* inStream) {
        inputStream = inStream;
        // Create a method to parse incoming request payload
        parsePayload(inputStream);
    }


    void parsePayload(InputStream inStream) {
        string savedByteCode = "";

        cout << "PARSE PAYLOAD" << endl;;

        //Scanner scanner = new Scanner(inStream);

        // Need to know Request type: GET or POST
        // Parse First Line
        reqType = scanner.next();
        cout << "The Request Type is: " << endl;
        String temp = "";


        string dataKeys[] = {"Date", "Keyword", "Caption", "File"};
        int currentKey = 0;
        int maxKey = 4;
        boolean endOfDataReached = false;
        while(!endOfDataReached && currentKey < maxKey) {
            // Print each token.
            temp = scanner.nextLine();
            
            // Check and Set User-Agent
            if (temp.startsWith("User-Agent:")){
                reqUserAgent = "browser";
            }
            if (temp.startsWith("User-Agent: cli")){
                reqUserAgent = "cli";
            } 


            if (temp.startsWith("--boundary")) {
                // Start of the current body from the form data
                String currBody = scanner.nextLine();
                String currValue = "";

                // Loop until next boundary is reached
                while (!currBody.trim().equals("")) {
                    currValue = currBody;           // Store previous line's value
                    currBody = scanner.nextLine();  // Get next line
                    System.out.println("CURRBODY: " + currBody);
                }

                currValue = scanner.nextLine();

                // Store value in hashmap
                FormData.put(dataKeys[currentKey], currValue);
                System.out.println("PUT IN MAP: " + dataKeys[currentKey] + ", " + currValue);
                currentKey++;
            }

            if (currentKey == 3 && temp.startsWith("--boundary")){

                // At the File Body Part. Currently at "--boundary"
                String iterateByteCode = scanner.nextLine();

                // Parse File Body Part..
                while(!(iterateByteCode.trim().equals(""))) {

                    // Keep iterating until you find empty line, which tells us to start reading at the next line.
                    System.out.println("NOT AT EMPTY LINE" + iterateByteCode);
                    iterateByteCode = scanner.nextLine();
                }
                temp = scanner.nextLine();
            }
         

            while ((!temp.trim().equals("")) && currentKey == 3 && !(temp.equals("--boundary--"))){
                savedByteCode = savedByteCode + temp;

                temp = scanner.nextLine();
            }
            
            if (temp.startsWith("Accept-Language:") || temp.contains("--boundary--")){
                System.out.println("THIS SHOULD BE THE LAST ONE");
                imageByteCode = savedByteCode;
                endOfDataReached = true;
            }
        }





        System.out.println("Made it here");
        // scanner.close();
    }
    

    private:
        istringstream* inputStream;
        string reqType;
        string reqUserAgent;
        pair<string, string> FormData;
        string imageByteCode;
};