#pragma once

#include "Request.hpp"
#include "Response.hpp"

class Servlet {
    public:
        virtual void doGet(Response res, Request req) = 0;
        virtual void doPos(Response res, Request req) = 0;
};