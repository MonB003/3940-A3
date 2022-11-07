#pragma once

// #include "Request.hpp"
// #include "Response.hpp"

class Request;
class Response;

class Servlet {
    public:
        virtual int getSocket() = 0;
        virtual string get(Response &response, Request &request) = 0;
        virtual void post(Response &response, Request &request) = 0;
};