Assignment 3 README

SETUP:
=================================

Compile server.exe
g++ main.cpp ServerThread.cpp Request.cpp ServerSocket.cpp Response.cpp Socket.cpp UploadServlet.cpp base64.cpp -o server

Compile client.exe
g++ ClientServlet.cpp Socket.cpp base64.cpp -o client

Steps to run CLI:
Step 1: Execute Server.exe
Step 2: Execute Client.exe
Step 3: Follow on screen instructions prompted by Client.exe

Steps to run browser:
Step 1: In the Cgywin terminal, execute ./server
Step 2: In a browser, go to http://localhost:8889/
Step 3: Select a file to upload, type a caption and select a date, then press the submit button.

=================================


CONTRIBUTIONS:
=================================

Name: Jay Wang
ID: A01291640
- Worked on the Parsing Payload recieved from Socket connection
- Worked on CLI Client
    - Created and sent off POST Request
- Finished off the UploadServlet.

=================================

Name: Monica Bacatan
ID: A01268930
- Worked on parsing the payload from the browser
- Helped set up the getters and setters for classes
- Helped set up method for getting user input from the CLI
- Helped set up CLI post request body layout
- Helped create a method to get all files from a directory

=================================

Name: Brad Masciotra
ID: A01247718
- Set up Project Structure
- Parsing the payload from the browser
- Set up socket connection and accepting methods

=================================

Name: Will Whitfield
ID: A01267214
- Created and iterated the majority of UploadServlet post request 
    - Printed the list of image names in the images directory
- Worked on CLI Client